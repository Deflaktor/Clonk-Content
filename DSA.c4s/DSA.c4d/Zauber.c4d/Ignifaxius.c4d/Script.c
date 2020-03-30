#strict

#include _ZTE

Activate:
  SetLocal(0,Par(0));
  SetLocal(2,CalcPower(Local(0)));
  DoCon(Local(2));
  Sound("Firecast");
  if(Equal(GetDir(Par(0)),DIR_Left())) Call("Liii");
  if(Equal(GetDir(Par(0)),DIR_Right())) Call("Reee");
  return(1);

Liii:
  SetPosition(Sum(GetX(),-9),GetY());
  SetAction("Los");
  SetDir(DIR_Right());
  SetComDir(COMD_Left());
  SetXDir(-70);
  return(1);

Reee:
  SetPosition(Sum(GetX(),9),GetY());
  SetAction("Los");
  SetDir(DIR_Left());
  SetComDir(COMD_Right());
  SetXDir(70);
  return(1);

Hit:
  // Basis-Schaden
  SetVar(0,30);
  // Zusatz-Schaden durch Magie-Fertigkeit
  SetVar(1,CalcDamage(Var(0),Local(2)));
  SetVar(2,(30+Var(1))/2);
  while(Var(1)>30) {
    Explode(Var(2));
    SetVar(1,Var(1)-30);
  }
  Explode(Var(2));
  //CastObjects(HF3A, 10+Local(2)/30, 20+Local(2)/20 );
  RemoveObject();
  return(1);

CheckforHit:
  if(GreaterThan(GetActTime(),150)) RemoveObject();
  if(SetLocal(1,FindObject(0,-7,-7,14,14,OCF_Living(),0,0,NoContainer()))) 
     if(Not(SEqual(GetAction(Local(1)), "Dead")))
        if(Not(Equal(Local(1),Local(0))))
         Call("Hit");
  return(1);

AbleToCastByMagier:
  return(1);