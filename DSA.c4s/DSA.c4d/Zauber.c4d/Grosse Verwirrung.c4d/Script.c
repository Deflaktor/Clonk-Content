Activate:
  SetLocal(0,Par(0));
  if(Equal(GetDir(Par(0)),DIR_Left())) Call("Liii");
  if(Equal(GetDir(Par(0)),DIR_Right())) Call("Reee");
  return(1);

Liii:
  SetPosition(Sum(GetX(),-5),GetY());
  SetAction("Los");
  SetDir(DIR_Left());
  SetComDir(COMD_Left());
  SetXDir(-40);
  return(1);

Reee:
  SetPosition(Sum(GetX(),5),GetY());
  SetAction("Los");
  SetDir(DIR_Left());
  SetComDir(COMD_Right());
  SetXDir(40);
  return(1);

CheckforHit:
  if(GreaterThan(GetActTime(),150)) RemoveObject();
  if(SetLocal(1,FindObject(0,-7,-7,14,14,OCF_Living(),0,0,NoContainer()))) 
     if(Not(SEqual(GetAction(Local(1)), "Dead")))
        if(Not(Equal(Local(1),Local(0))))
         Call("hahaha");
  return(1);

hahaha:
  SetXDir(0);
  SetComDir(COMD_Stop());
  SetAction("Daswars");
  return(1);

BleibDa:
  if(GreaterThan(GetActTime(), 2000)) Call("Hit");
  SetComDir(COMD_Stop(),Local(1));
  SetVar(1,Random(4));
  if(Equal(Var(1),0)) Call("Links");
  if(Equal(Var(1),1)) Call("Rechts");
  if(Equal(Var(1),2)) Call("Unten");
  if(Equal(Var(1),3)) Call("Oben");
  //if(Equal(Var(1),4)) Call("Graben");
  //if(Equal(Var(1),5)) Call("Werfen");
  return(1);

Links:
  SetComDir(COMD_Left(),Local(1));
  return(1);
Rechts:
  SetComDir(COMD_Right(),Local(1));
  return(1);
Unten:
  SetComDir(COMD_Stop(),Local(1));
  SetComDir(COMD_Down(),Local(1));
  return(1);
Oben:
  SetComDir(COMD_Up(),Local(1));
  return(1);

Hit:
  RemoveObject();
  return(1);

AbleToCastByMagier:
  return(1);