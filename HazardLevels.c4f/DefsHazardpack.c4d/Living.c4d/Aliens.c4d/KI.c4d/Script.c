/*-- Neues Objekt --*/

#strict
#include _CL_

local target, lastSightX, lastSightY, lastSightTime;

Initialize:
  SetAction("Walk");
  lastSightTime=1000;
  Refit();
  return(1);

Activity:
  _inherited();
  if(target) {
    lastSightX = GetX(target);
	lastSightY = GetY(target);
    if(!GetAlive(target)) {
	  target = 0;
	  lastSightTime = 1000;
	} else if(!GetTarget(target)||!PathFree(GetX(),GetY(),GetX(target),GetY(target))) {
	  lastSightTime = 0;
      target = 0;
	}
  } else if(lastSightTime!=-1)
    lastSightTime++;
  return(1);

Platzen:
  while(SetVar(0,Contents())) Exit(Var(0),0,-5,Random(360),GetXDir(),GetYDir());
  if(Global(0)) {
    var speed, angle, size;
    speed = Sqrt(GetXDir()*GetXDir()+GetYDir()*GetYDir());
    angle = Angle(0,0,GetXDir(),GetYDir());
    size = GetDefCoreVal("Height","DefCore",GetID());
    CastObjectsX(MEAT,(size/40)*GetCon()*GetCon()/4000,Max(speed,20,size*2),0,0,90,270,false);
    //CastObjectsX(BL7K,80,speed+20,0,0,angle,180,false);
    CastObjects(BL7K,size*GetCon()*GetCon()/4000,speed+20+size);
    Sound("Zerquetschen");
    RemoveObject();
  }
  SetYDir(GetYDir()-50);
  Kill();
  return(1);

public Redefine:
  ChangeDef(Par(0));
  SetAction("Walk");
  return(1);

Shrink:
  Sound("Teleport");
  // schrumpfe maximal um 25
  DoCon(Max(25-GetCon(), -25));
  // Gib Punkte
  if(Par(0)!=GetOwner())
    DoScore( Par(0), +10 );
  return(1); 

Refit:
  SetPhysical("Energy",GetDefCoreVal("Energy", "Physical", GetID())/100*(Global(4)+100),2);
  DoEnergy(9999);
  return(1);

Damage:
  if(Par(1)!=-1)
    if(Var(0)=GetTarget(GetCrew(Par(1))))
      target=Var(0);
  Bluten(Par(0));
  return(1);

CatchBlow:
  if(GetOwner(Par(1))!=-1)
    if(Var(0)=GetTarget(GetCrew(GetOwner(Par(1)))))
      target=Var(0);
  return(1);

Bluten:
  if(!Global(0))
    return(2);
  /*if(Par(0)==0)
    CastObjects(BL7K,20*GetCon()/100,20);
  if(Par(0)!=0)*/
    CastObjects(BL7K,Par(0)*GetCon()/100,20);
  return(1);