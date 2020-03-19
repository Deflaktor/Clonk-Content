/*-- Tür --*/

#strict

ControlLeft:
SetLocal(0,1);
return(1);

ControlRight:
SetLocal();
return(1);

Trigger:
  Local(0)=!Local(0);
  return(1);
  
IsTriggerable:
  return(1);

CheckArea:
  if(Local(0))
    Open();
  else
    Close();
  return(1);
  // Aktiv?
  if(!Local())
    return(Close());
  // Clonk im Bereich suchen
  SetVar(0,FindObject(0, -15,-16,30,32, OCF_CrewMember()));
  // Clonk da und steht, öffnen
  if (Var(0)) 
    if( Equal( GetComDir( Var(0) ),COMD_Stop() ) ) 
      Open();
  // Wenn kein Clonk da, schließen
  if (Not(Var(0))) 
    Close();
 return(1);

Open:
  if(Not(ActIdle())) return(1);
  SetAction("OpenDoor");
  return(1);

Close:
  if(Not(SEqual(GetAction(),"DoorOpen"))) return(1);
  SetAction("CloseDoor");
  return(1);

Initialize:
  PutSolidMask();
  UpdateTransferZone();
  return(1);
     
RemoveSolidMask:
  SetSolidMask();
  return(1);

PutSolidMask:
  SetSolidMask(1,0,5,30,1,0);
  return(1);
        
SoundOpen:
  Sound("Airlock1");
  return(1);
SoundClose:
  Sound("Airlock2");
  return(1);

/* Transfer */

protected UpdateTransferZone:
  SetTransferZone(0);
  return(1);
