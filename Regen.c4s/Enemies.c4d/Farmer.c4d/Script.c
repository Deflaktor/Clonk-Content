
#strict 2

local cast, delay, radius;

protected func Initialize() {
  SetAction("Ghost");
  cast = 4;
  delay = 0;
  SetOwner(-1);
  FadeIn(this(),128,0,3);
  SetObjAlpha(255);
  radius=12;
  return true;
}

public func SetBlast(int pRadius) {
  radius = pRadius;
}

protected func Activity() {
  if(GetEnergy()<=0) {
    CastObjects(SPRK,15,35);
	RemoveObject();
  }
  SetObjRed((40-GetEnergy())*4);
  delay++;
  var obj=FindObject(0,0,0,-1,-1,OCF_CrewMember,0,0,NoContainer());
  if(!obj) obj=FindObject(0,0,0,-1,-1,OCF_CrewMember,0,0,0);
  if(!obj) return false;
  if(GetX(obj)<GetX())
	SetDir(DIR_Right);
  else
	SetDir(DIR_Left);
  if(delay>6&&cast>0) {
	var angle=Angle(GetX(),GetY(),GetX(obj),GetY(obj));
    CastMeteor(0,angle,RandomX(radius-radius/4,radius+radius/4),GetOwner());
	cast--;
	delay=4;
  } else if(cast<=0) {
    FadeOut(this(),255,0,10);
  }
  return true;
}

protected func CatchBlow(int iLevel, object pBy) {
  if(GetEnergy()<=0)
    return(1);
  /*if(GetEnergy()>0)
    AddEffect("TakeDamage", this(), 150, 5, 0, GetID(), 360);*/
  Sound("Corrode");
  DoEnergy(-10+iLevel);
  pBy->SetXDir(-GetXDir(pBy)/3);
  pBy->SetYDir(GetYDir(pBy)+5);
  SetObjRed((40-GetEnergy())*4);
  if(GetEnergy()<=0) {
    CastObjects(SPRK,15,35);
	RemoveObject();
  }
  pBy->~Hit();
  return(1);
}

protected func Destroy() {
  CastObjects(SPRK,20,50);
  return(1);
}

public func CastMeteor(id idObj,int iDir, int iExplo, int iOwner) { 
  // Standardhagel besteht aus Meteoriten
  if(!idObj) idObj=METO;
  var xspd = Sin(iDir,RandomX(50,75));
  var yspd = -Cos(iDir,RandomX(50,75))-10;
  // Einen Meteoriten gen Erdreich schleudern
  var pMeteor = CreateObject(idObj,xspd/4,yspd/4, -1);
  SetSpeed(xspd,yspd,pMeteor);
  // Controller korrigieren
  SetController(iOwner,pMeteor);
  // Explosionsradius anpassen
  if(iExplo && idObj==METO) pMeteor->METO::SetExplosionBase(iExplo);
}



// EFFECTS



protected func FxTakeDamageStart (object pTarget, int iNumber, int iTemp, int iDuration)
{
  if(iTemp) return(0);
  EffectVar(0,pTarget,iNumber)=360;
  pTarget->Sound("Corrode");
}
  
protected func FxTakeDamageTimer(object pTarget, int iEffectNumber, int iEffectTime)
{
  var iTime = EffectVar(0, pTarget, iEffectNumber) -= 72;
  
  /*var iAlpha = 70 * Min(GetDuration(), GetDuration()-iTime) / GetDuration();
  if(iAlpha>50)
    iAlpha=50;*/


  SetObjAlpha(128,pTarget);
  SetObjRed(128-40+Cos(iTime, 40),pTarget);
  SetObjAlpha(128,pTarget);

  // Nach Ablauf der Zeit wird der Effekt gelöscht
  if (iTime <= 0) {
    SetObjRed(0,pTarget);
    return(-1);
  }
}

protected func FxTakeDamageStop(object pTarget, int iEffectNumber, int iReason, bool fTemp)
{
  // Keine temporären Aufrufe
  if (fTemp) return(0);
  
  SetObjRed(0,pTarget);
  SetObjAlpha(128,pTarget);
}

protected func FxTakeDamageEffect(string szNewEffectName)
{
  // gleichen Effekt zusammenfassen
  if(szNewEffectName == "TakeDamage") return(-2);
}

protected func FxTakeDamageAdd(object pTarget, int iNumber, string szNewEffectName, int iNewEffectTimer, int iDuration) {
  // Effekt übernehmen
  Sound("Corrode");
  EffectVar(0,pTarget,iNumber) = Min( EffectVar(0,pTarget,iNumber)+iDuration,360);
}

protected func SetObjAlpha(int byAlpha,object pObj) {
	var dwClrMod=GetClrModulation(pObj);
	if(dwClrMod == 0) dwClrMod = RGBa(255,255,255,0);

	dwClrMod = SetRGBaValue(dwClrMod,byAlpha,0);
 	return(SetClrModulation(dwClrMod, pObj));
}

protected func SetObjRed(int byRed,object pObj) {
	var dwClrMod=GetClrModulation(pObj);
	
	dwClrMod = SetRGBaValue(dwClrMod,255-byRed,2);
	dwClrMod = SetRGBaValue(dwClrMod,255-byRed,3);
 	return(SetClrModulation(dwClrMod, pObj));
}

protected func FxFadeOutStart(target, no, temp, level, amount) {
	if(!level) {
		EffectVar(1, target, no) = 255;
	} else {
		EffectVar(1, target, no) = level;
	}

	EffectVar(2, target, no) = Max(1,amount);
}

protected func FxFadeOutTimer(target, no) {
	EffectVar(0, target, no)+= EffectVar(2, target, no);
	SetObjAlpha(EffectVar(0, target, no),target);
	
	if (EffectVar(0, target, no) >= EffectVar(1, target, no)) { 
		if (EffectVar(1, target, no) >= 255) {
			RemoveObject(target); 
			return(-1); 
		}
	}
}

protected func FadeOut(object pObject, int level, bool fFast, int iAmount) {
	if (!pObject) {
		pObject = this;
	}

	if (GetEffect("*FadeOut*", pObject)) {
		return;
	}
	if (fFast) {
		return AddEffect("FadeOut", pObject, 101, 1,0,GetID(),level, iAmount);
	}
	return(AddEffect("FadeOut", pObject, 101, 2,0,GetID(),level, iAmount));
}

protected func FxFadeInStart(target, no, temp, level, amount) {
	EffectVar(0, target, no) = 255;
	EffectVar(1, target, no) = level;
	EffectVar(2, target, no) = Max(1,amount);
}

protected func FxFadeInTimer(target, no) {
	EffectVar(0, target, no)-=EffectVar(2, target, no);
	SetObjAlpha(EffectVar(0, target, no),target);
	
	if (EffectVar(0, target, no) <= EffectVar(1, target, no)) { 
		return(-1); 
	}
}

protected func FadeIn(object pObject, int level, bool fFast, int iAmount) {
	if(!pObject) {
		pObject = this;
	}
	if (GetEffect("*FadeIn*", pObject)) {
		return;
	}
	if (fFast) {
		return AddEffect("FadeIn", pObject, 101, 1,0,GetID(),level, iAmount);
	}
	return(AddEffect("FadeIn", pObject, 101, 2,0,GetID(),level, iAmount));
}

protected func StopFading(object pObject) {
	if(!pObject) {
		pObject = this;
	}
	var eff = GetEffectCount("*Fade*",pObject);
	for(eff; eff; eff--) {
		RemoveEffect("*Fade*",pObject);
	}
}


protected func IsFading(object pObject) {
	if(!pObject) {
		pObject = this;
	}
	var eff = GetEffectCount("*Fade*",pObject);
	return (eff);
}