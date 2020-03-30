Activate:
  SetLocal(1,Par(0));
  if(Equal(GetDir(Par(0)),DIR_Left())) SetAction("gumpli");
  if(Equal(GetDir(Par(0)),DIR_Right())) SetAction("gumpre");
  return(1);

rekz:
  ObjectSetAction(Local(1),"Jump");
  SetXDir(80,Local(1));
  SetYDir(-50,Local(1));
  RemoveObject();
  return(1);

linkz:
  ObjectSetAction(Local(1),"Jump");
  SetXDir(-80,Local(1));
  SetYDir(-50,Local(1));
  RemoveObject();
  return(1);

AbleToCastByElf:
  return(1);
AbleToCastByMagier:
  return(1);