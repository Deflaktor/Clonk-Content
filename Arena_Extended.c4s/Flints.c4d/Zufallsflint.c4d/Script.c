#strict
#include PRNT

static letzterZufall;


/* Zufallsflint */

/* Aufschlag */

ZufallsQuatsch:
  letzterZufall = FrameCounter();
  var rand;
  rand = Random(14);
  Sound("EventDo");
  if(rand<=3) if(ZeichneFlintKreis()) return(1);
  if(rand==4) return(Platztausch());
  if(rand==5) if(!Random(10)) return(AllesLitten());
  if(rand==6) return(Zeitfeld());
  if(rand==7) return(HalbeExplosionen());
  if(rand==8) return(KeineGrenzen());
  if(rand==9) return(VielErde());
  if(rand==10) if(!Random(18)) return(AlleVerbessern());
  if(rand==11) if(!Random(20)) return(Bombeneinheit());
  if(rand==12) return(Panzer());
  if(rand==13) return(Saugen());
  return(ZufallsQuatsch());

Hit:
  if(FrameCounter()-letzterZufall>500&&!Random(10)||FrameCounter()-letzterZufall>30*40&&!Random(2)||GetOwner()!=-1&&!Random(5)) {
    return(ZufallsQuatsch());
  }
  // Explodieren mit einer Explosionsstärke von 1 - 60
  Explode(SetVar(0,Sum(1,Random(60))));
  // Das Hilfsobjekt erzeugen und bei diesem RandomHelps aufrufen
  ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
  // Stärke über dem Hilfsobjekt auslesen
  Message("Stärke: %d/60",Var(1),Var(0));
  return(1);
  
Saugen:
  SetLocal(0,CreateObject(SWE7,0,0,GetOwner()));
  ObjectSetAction(Local(0),"Implode");
  DoCon(3000,Local(0));
  ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
  Message("Saugen!",Var(1));
  return(RemoveObject());
  
Panzer:
  CreateObject(PM7K,0,0,GetOwner());
  CastObjects(_PRK,15,20);
  ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
  Message("Panzer!",Var(1));
  return(RemoveObject());
  
Zeitfeld:
  CreateObject(_SDC,0,0,GetOwner());
  ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
  Message("Zeitfeld!",Var(1));
  return(RemoveObject());
  
HalbeExplosionen:
  CreateObject(_HAE,0,0,GetOwner());
  ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
  Message("Kleine Explosionen!",Var(1));
  return(RemoveObject());
  
KeineGrenzen:
  CreateObject(_NOB,0,0,GetOwner());
  ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
  Message("Keine Grenzen!",Var(1));
  return(RemoveObject());
  
VielErde:
  ShakeFree(GetX(),GetY(),20);
  CastPXS("Earth", 10000, 160,0,-15);
  Sound("Earthquake");
  ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
  Message("Erdaufschüttung!",Var(1));
  return(RemoveObject());
  
ZeichneFlintKreis:
  if(GetY()>LandscapeHeight()*2/3&&GetY()<LandscapeHeight()-150) {
	  VieleckZeichnen("Flint", 100, 72);
	  Sound("Magic1");
	  ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
	  Message("Flint-Gestein!",Var(1));
	  return(RemoveObject());
  }
  return(0);
  
VieleckZeichnen:
  var material = Par(0);
  var radius = Par(1);
  var ecken = BoundBy(Par(2), 3, 360);
  var x = GetX() + Par(3);
  var y = GetY() + Par(4);
  var underground = 1;
  for (var winkel = 0; winkel<360; winkel+=360/ecken) {
    var x1, x2, y1, y2;
    x1 = x + Sin(winkel, radius);
    y1 = y + Cos(winkel, radius);
    if(GetMaterial(x1 - GetX(), y1 - GetY())==Material("Sky"))
      underground = 0;
  }
  underground=1;
  for (var winkel = 0; winkel<360; winkel+=360/ecken) {
    var x1, x2, y1, y2;
    x1 = x + Sin(winkel, radius);
    y1 = y + Cos(winkel, radius);
    x2 = x + Sin(winkel+360/ecken, radius);
    y2 = y + Cos(winkel+360/ecken, radius);
	
    DrawMaterialQuad(material,x,y,x1,y1,x2,y2,x,y,underground);
  }
  return(1);
  
AlleVerbessern:
    while(SetVar(0,FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,0,Var(0)))) 
      Aufwerten(Var(0));
	Sound("Magic1");
	ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
	Message("Aufwertung!",Var(1));
	return(RemoveObject());
	
AllesLitten:
    //while(SetVar(0,FindObject(0,0,0,0,0,OCF_Collectible(),0,0,0,Var(0)))) 
    //  LitUp(Var(0));
	Sound("Magic1");
	ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
	SetLocal(0,1,Var(1));
	Message("Zufalls Zündung!",Var(1));
	return(RemoveObject());
  
Aufwerten:
  SetPhysical("Walk", GetPhysical("Walk",1,Par(0))*2, 2, Par(0));
  SetPhysical("Energy", GetPhysical("Energy",1,Par(0))*3/2, 2, Par(0));
  SetPhysical("Jump", GetPhysical("Jump",1,Par(0))*3/2, 2, Par(0));
  SetPhysical("Scale", GetPhysical("Scale",1,Par(0))*3/2, 2, Par(0));
  SetPhysical("Hangle", GetPhysical("Hangle",1,Par(0))*3/2, 2, Par(0));
  SetPhysical("Dig", GetPhysical("Dig",1,Par(0))*3/2, 2, Par(0));
  SetPhysical("Throw", GetPhysical("Throw",1,Par(0))*3/2, 2, Par(0));
  SetColorDw(SetRGBaValue(GetColorDw(Par(0)),127,0),Par(0));
  DoEnergy(10000,Par(0));
  return(1);
  
Platztausch:
	var count,repeat;
	count=ObjectCount(0,0,0,0,0,OCF_CrewMember()|OCF_Alive());
	count-=ObjectCount(GIK1);
	count-=ObjectCount(BIG1);
	count-=ObjectCount(WIG1);
	repeat = count*2;
	var firstObj, secondObj;
	//for(var i=0;i<repeat;i++) {
	  while(secondObj = FindObject(0,0,0,0,0,OCF_CrewMember()|OCF_Alive(),0,0,0,secondObj)) {
	    if(GetCon(secondObj)!=100) continue;
	    if(firstObj) {
		  SwapTwoObjects(firstObj,secondObj);
		}
		firstObj = secondObj;
	  }
	//}
	ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
	Sound("capeopen");
	Message("Platztausch!",Var(1));
	return(RemoveObject());
  
Bombeneinheit:
    while(SetVar(0,FindObject(0,0,0,0,0,OCF_Collectible(),0,0,0,Var(0)))) 
      if(GetID(Var(0))!=GetID()&&GetID(Var(0))!=CHST)
        ChangeDef(GetID(),Var(0));
	Sound("change");
	ObjectCall(SetVar(1,CreateObject(_RN1,0,-45)),"RandomHelps");
	Message("Bombeneinheit!",Var(1));
	return(RemoveObject());

public func SwapTwoObjects(object obj, object obj2) {
  var x,y,r,xdir,ydir,rdir,action,phase;
  x=GetX(obj);
  y=GetY(obj);
  r=GetR(obj);
  xdir=GetXDir(obj);
  ydir=GetYDir(obj);
  rdir=GetRDir(obj);
  action=obj->GetAction();
  phase=obj->GetPhase();
  obj->SetPosition(GetX(obj2),GetY(obj2));
  obj->SetR(GetR(obj2));
  obj->SetXDir(GetXDir(obj2));
  obj->SetYDir(GetYDir(obj2));
  obj->SetRDir(GetRDir(obj2));
  obj->SetAction(obj2->GetAction());
  obj->SetPhase(obj2->GetPhase());
  obj2->SetPosition(x,y);
  obj2->SetR(r);
  obj2->SetXDir(xdir);
  obj2->SetYDir(ydir);
  obj2->SetRDir(rdir);
  obj2->SetAction(action);
  obj2->SetPhase(phase);
}
  
/* Produkteigenschaften */

IsChemicalProduct: return(1);