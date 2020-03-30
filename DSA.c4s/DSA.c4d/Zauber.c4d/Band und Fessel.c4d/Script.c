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
  SetDir(DIR_Right());
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
  SetDir(DIR_Left());
  SetComDir(COMD_Stop());
  SetLocal(2,GetX(this()));
  SetAction("Daswars");
  return(1);

BleibDa:
  if(GreaterThan(GetActTime(), 2000)) Call("Hit");
  if(GreaterThan(Sub(GetX(Local(1)),Local(2)),30)) Call("liiinks");
  if(GreaterThan(Sub(Local(2),GetX(Local(1))),30)) Call("reeekts");
  return(1);

liiinks:
  SetComDir(COMD_Left(),Local(1));
  return(1);

reeekts:
  SetComDir(COMD_Right(),Local(1));
  return(1);

AbleToCastByElf:
  return(1);

Hit:
  RemoveObject();
  return(1);

AbleToCastByMagier:
  return(1);