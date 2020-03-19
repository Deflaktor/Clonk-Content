CheckArea:
  // Clonk im Bereich suchen
  SetVar(0,FindObject(0, -15,-16,30,32, OCF_CrewMember()));
  // Clonk da und steht, öffnen
  if (Var(0)) 
      if(FindContents( _RDC, Var(0) ) )
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
  Sound("Airlock2");
  return(1);