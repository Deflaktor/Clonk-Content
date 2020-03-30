#strict

ActivateEntrance:
  SetCommand(Par(),"None");
  if(
    GameCall( "NoTankStealing" )
 && Hostile(GetOwner(),GetOwner(Par()))
  )
    return(1);
  if (BitAnd(GetOCF(Par(0)),OCF_CrewMember()))
    if (IsOccupied())
      return(0,Message("Panzer ist|schon besetzt!",this()));
  Enter(Local(),Par());
  Sound("Airlock1");
  return(1);


/* Status */

public IsOccupied:
  if (ObjectCount(0,0,0,0,0,OCF_CrewMember(),0,0,GetActionTarget()))
    return(1);
  return(0);
