#strict
#include _POV

Dmg: return(20);

Launch:
  if (Equal(Par(0),DIR_Left())) Local(0)=-150;
  if (Equal(Par(0),DIR_Right())) Local(0)=150;
 Local(1)=1;
 SetLocal(2,2);
 SetLocal(3,10);
 if(Equal(Random(10),1)) return(stark());
 return(SetAction("Flug"));

Flug:
  if(Var(0)=CheckHit(-7,-10,14,20))
    return(HitL(Var(0)));
  SetXDir(Local(0));
  SetYDir(Local(1));
  return(1);

Hit:
  ObjectCall(CreateObject(EXPL),"Launch",Local(3));
  RemoveObject();
  return(1);

HitL:
  if(SEqual(GetAction(Par(0)),"Dead"))  return(1);
  DoEnergy(-Dmg(),Par(0));
  DoDamage(Dmg(),Par(0));
  Sound("ProjectileHit*");
  ObjectCall(Par(0),"Bluten", 60);
  SetLocal(1,Sum(Local(1),1));
return(1);

stark:
  SetLocal(2,3);
  SetLocal(3,15);
  SetXDir(Mul(GetXDir(),2));
  SetAction("SFlug");
return(1);