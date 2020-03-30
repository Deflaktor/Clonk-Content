/*-- Dronentür --*/

#strict

CheckArea:
  if(!GetEnergy()) {
    if(GetAction() eq "DoorActive")
      SetAction("Idle");
    return(Close());
  }
  if(GetAction() eq "Idle")
    SetAction("DoorActive");
  // Drone im Bereich suchen
  SetVar(0,FindObject(0, -15,-16,30,32, OCF_CrewMember()));
  // Drone da, öffnen
  if (Var(0)) 
    if( Equal( GetComDir( Var(0) ),COMD_Stop() ) || GetAction(Var(0)) eq "Swim" ) 
      Open();
  // Wenn keine Drone da, schließen
  if (Not(Var(0))) 
    Close();
 return(1);

GetEnergy:
  while(SetVar(0,FindObject(_GEN,0,0,0,0,0,0,0,0,Var(0))))
    if(!SEqual(GetAction(Var(0)),"Running"))
      return(0);
  return(1);

Open:
  if(!(GetAction() eq "DoorActive")) return(1);
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
  SetSolidMask(1,0,2,32,1,0);
  return(1);
        
SoundOpen:
  Sound("Airlock1");
  return(1);
SoundClose:
  if(GetEnergy())
    if(GetAction() eq "Idle")
      SetAction("DoorActive");
  Sound("Airlock2");
  return(1);
 
Damage:
  if ( LessThan( GetDamage(), 1000 ) ) return(0);
  CastObjects(_DF2,3,50,0,-5);
  CastObjects(SHRP,10,30,0,0);
  RemoveObject();  
  Sound("Discharge");
  Sound("Blast2");
  return(1);


  /* Transfer */

protected UpdateTransferZone:
  SetTransferZone(-11,-16,22,32);
  return(1);
  
protected ControlTransfer: // C4Object* pObj, int iTx, int iTy
  // Tür offen: Clonk soll einfach weiterlaufen
  if (SEqual(GetAction(),"DoorOpen")) return(0);
  // Durchgang nach rechts
  if (GreaterThan(Par(1),GetX()))
    // Objekt soll links von der Tür anhalten
    return(AddCommand(Par(0),"MoveTo",0,Sum(GetX(),-10),GetY()));
  // Durchgang nach links
  if (LessThan(Par(1),GetX()))
    // Objekt soll rechts von der Tür anhalten
    return(AddCommand(Par(0),"MoveTo",0,Sum(GetX(),+10),GetY()));
  // Transfer nicht möglich
  return(0);