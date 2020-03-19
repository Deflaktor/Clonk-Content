/*-- Große Tür --*/

#strict

CheckArea:
  // Clonk im Bereich suchen
  SetVar(0,FindObject(0, -15,-24,30,48, OCF_CrewMember()));
  // Clonk da und steht, öffnen
  if (Var(0)) 
  // if( Equal( GetComDir( Var(0) ),COMD_Stop() )|| GetAction(Var(0)) eq "Swim" ) 
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
  SetSolidMask(1,0,2,48,1,0);
  return(1);
        
SoundOpen:
  Sound("Airlock1");
  return(1);
SoundClose:
  Sound("Airlock2");
  return(1);
 
Damage:
  if ( LessThan( GetDamage(), 140 ) ) return(0);
  CastObjects(_DF1,6,50,0,-5);
  CastObjects(SHRP,20,30,0,0);
  RemoveObject();  
  Sound("Discharge");
  Sound("Blast2");
  return(1);
  
/* Transfer */

protected UpdateTransferZone:
  SetTransferZone(-11,-24,22,48);
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