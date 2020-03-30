Activate:
  Exit(this());
  SetLocal(3,GetX(Par(0)));
  SetLocal(4,GetY(Par(0)));
  if(Equal(GetDir(Par(0)),DIR_Left())) Call("Links");
  if(Equal(GetDir(Par(0)),DIR_Right())) Call("Rechts");
  return(1);

Links:
  //Exit(this(),-30,-19);
  SetPosition(Sum(Local(3),-28),Sum(Local(4),-10));
  SetAction("Los");
  return(1);

FindHammel:
  if(GreaterThan(GetActTime(),150)) Call("daswars");
  if(SetLocal(1,FindObject(0,-10,0,20,22,OCF_Living()))) SetAction("SeiNett");
  return(1);

Rechts:
  //Exit(this(),30,-19);
  SetPosition(Sum(Local(3),28),Sum(Local(4),-10));
  SetAction("Los");
  return(1);


GibLeben:
  if(GreaterThan(GetActTime(),280)) Call("daswars");
  if(FindObject(GetID(Local(1)),-10,0,20,25)) Call("Korrekt");
  return(1);

Korrekt:
  if(OnFire(Local(1))) Extinguish(Local(1));
  DoEnergy(+1,Local(1));
  return(1);

daswars:
  RemoveObject();
  return(1);

AbleToCastByElf:
  return(1);

AbleToCastByMagier:
  return(1);