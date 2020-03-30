#strict

#include _ZTE

Activate:
  SetLocal(0,Par(0));
  SetLocal(2,CalcPower(Local(0)));
  DoCon(Local(2));
  Sound("Darkcast");
  if(Equal(GetDir(Par(0)),DIR_Left())) Call("Liii");
  if(Equal(GetDir(Par(0)),DIR_Right())) Call("Reee");
  return(1);

Liii:
  SetPosition(Sum(GetX(),-7),GetY());
  SetAction("Los");
  SetDir(DIR_Right());
  SetComDir(COMD_Left());
  SetXDir(-50);
  return(1);

Reee:
  SetPosition(Sum(GetX(),7),GetY());
  SetAction("Los");
  SetDir(DIR_Left());
  SetComDir(COMD_Right());
  SetXDir(50);
  return(1);

Hit:
  RemoveObject();
  return(1);

CheckforHit:
  if(GreaterThan(GetActTime(),150)) RemoveObject();
  if(SetLocal(1,FindObject(0,-7,-9,14,18,OCF_Living(),0,0,NoContainer()))) 
     if(Not(SEqual(GetAction(Local(1)), "Dead")))
        if(Not(Equal(Local(1),Local(0))))
         Call("PaffPumm");
  return(1);

PaffPumm:
  // Basis-Schaden
  SetVar(0,7);
  // Zusatz-Schaden durch Magie-Fertigkeit
  SetVar(1,CalcDamage(Var(0),Local(2)));
  Punch(Local(1),Var(1));
  ObjectCall(Local(1),"TakeDamage",Var(1));
  RemoveObject();
  return(1);

AbleToCastByElf:
  return(1);

AbleToCastByMagier:
  return(1);