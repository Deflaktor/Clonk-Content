ActivateEntrance: 
  if (Not(ActIdle())) return(1);
  SetAction("OpenDoor");
  Sound("DoorOpen");
  return(1);
DoorIsOpen:
  SetEntrance(1);
  return(1);
DoorIsClosed:
  SetEntrance(0);
  Sound("DoorClose");
  return(1);
