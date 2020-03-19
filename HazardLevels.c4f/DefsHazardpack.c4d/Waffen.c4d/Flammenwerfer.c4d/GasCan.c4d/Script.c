#strict
#include _MOV

local incinerationCount;

Hit:
  Sound("ClonkHit*");
  return(1);

Damage:
  if(GetDamage()<10&&!OnFire())
    return(1);
  CastObjects(DFLM, 10, 15 );
  SetVar(0,CreateContents(_AE3));
  Exit(Var(0),0,0,Random(360), Sum(Random(7),-3), Sum(Random(3),-8), +10);
  Incinerate(Var(0));
  RemoveObject();
  ObjectCall(CreateObject(EXPL),"Launch",35); 
  return(1);

Initialize:
  return(1);

Incineration:
  incinerationCount++;
  if(incinerationCount<3)
    Extinguish();
  return(1);

HotLaserIncineration:
  incinerationCount = 100;
  Incinerate();
  return(1);

Timer:
  CoolDown();
  return(_inherited());
  
CoolDown:
  incinerationCount--;
  if(incinerationCount<0)
    incinerationCount=0;
  return(1);