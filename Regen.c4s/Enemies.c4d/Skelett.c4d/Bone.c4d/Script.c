/*-- Knochen --*/
// BBON-Effekt wird ggf. vom Bisonknochen (Western) angehaengt

#strict 2

local undead;

protected func Hit()
{
  Sound("WoodHit*");
}

protected func SetUndead(bool pUndead) {
  undead = pUndead;
  return(1);
}

protected func Departure(object pContainer) {
  if(GetID(pContainer)==KIL1)
    ScheduleCall(this(), "FadeOut", 34*10, 0, this());
}

/*protected func Entrance() {
  ClearScheduleCall(this(), "FadeOut");
}*/

protected func RejectEntrance(object pIntoObj) {
  return(undead||IsFading());
}

protected func Check() {
  if(!undead) return(1);
  if(  ObjectDistance( FindObject(0,0,0,-1,-1,OCF_CrewMember) ) < 50  ) {
    var obj=CreateObject(KIL1,0,10);
	obj->SetAlpha(0);
	RemoveObject();
  }
  return(1);
}

func IsAlchemContainer() { if(GetID() != BONE && GetID() != BBON) return(false); return(true); }
func AlchemProcessTime() { if(GetID() != BONE && GetID() != BBON) return(false); if(GetEffect("BBON", this()) || GetID() == BBON) return(140); return(120); }

func IsManaContainer() { if(GetID() != BONE && GetID() != BBON) return(false); return(true); }
func ManaProcessTime() { if(GetID() != BONE && GetID() != BBON) return(false); if(GetEffect("BBON", this()) || GetID() == BBON) return(280); return(240); }

protected func SellTo() {
  if(GetEffect("BBON", this())) return(BBON);
  return(GetID());
}



protected func SetObjAlpha(int byAlpha,object pObj) {
	var dwClrMod=GetClrModulation(pObj);
	if(dwClrMod == 0) dwClrMod = RGBa(255,255,255,0);

	dwClrMod = SetRGBaValue(dwClrMod,byAlpha,0);
 	return(SetClrModulation(dwClrMod, pObj));
}

protected func FxFadeOutStart(target, no, temp, level, amount) {
	if(!level) {
		EffectVar(1, target, no) = 255;
	} else {
		EffectVar(1, target, no) = level;
	}

	EffectVar(2, target, no) = Max(10,amount);
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


protected func IsFading(object pObject) {
	if(!pObject) {
		pObject = this;
	}
	var eff = GetEffectCount("*Fade*",pObject);
	return (eff);
}