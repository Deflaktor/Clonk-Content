#strict
#include _POV
 
Dmg: return(8);

Launch:
  if (Equal(Par(0),DIR_Left())) SetXDir(-100);
  if (Equal(Par(0),DIR_Right())) SetXDir(100);
 SetYDir(-5);
 SetAction("Flug");
 SetDir(Par(0));
 return(1);

Flug:
  if(Var(0)=CheckHit(-7,-10,14,20))
    return(HitL(Var(0)));
  SetYDir(4);
  return(1);

Hit:
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()*5/8);
  RemoveObject();
  return(1);

HitL:
 if(SEqual(GetAction(Par(0)),"Dead"))  return(1);
 DoEnergy(-Dmg(),Par(0));
 ObjectSetAction(Par(0),"Jump");
 SetXDir(Sum(GetXDir(Par(0)),Sum(-14,Mul(GetDir(),28))),Par(0));
 SetYDir(Sum(GetYDir(Par(0)),-9),Par(0));
 RemoveObject();
 return(1);
