#strict

protected Construction:
  SetLocal(5,CreateObject(BAS9,0,+8));
  return(1);
  
protected Destruction:
  if (Local(5)) RemoveObject(Local(5));
  return(1);

protected ActivateEntrance: 
  if (ActIdle()) SetAction("OpenDoor");
  return(1);

private OpenEntrance: 
  SetEntrance(1); 
  return(1);

private CloseEntrance: 
  SetEntrance(0);
  return(1);

private SoundDoorOpen: return(Sound("DoorOpen"));
private SoundDoorClose: return(Sound("DoorClose"));

public GetResearchBase:
  return(GLAZ);