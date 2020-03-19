/*-- Werkstatt --*/

#strict

// Tür
protected ActivateEntrance: 
  if (Not(ActIdle())) return(1);
  SetAction("OpenDoor");
  return(1);

private EntranceOpen:
  SetEntrance(1);
  return(1);
private EntranceClose:
  SetEntrance(0);
  return(1); 
  
private SoundOpen:
  Sound("Airlock1");
  return(1);  
private SoundClose:
  Sound("Airlock2");
  return(1);  

/* Produktion */

private ContentsCheck:
  // Noch aktiv
  if (Not(ActIdle())) return(0);
  // Inhaltscheck
  if(Var()=FindContents(TIR1)) {
    RemoveObject(Var());
    SetAction("Build");
   }
  return(1);

private Fertig:
  // Noch nicht fertig
  if (LessThan(GetActTime(),35)) return(0);
  // Fertig
  SetAction("Idle");
  // Inhalt auswerfen
  SetCommand(CreateContents(_MED),"Exit");
  return(1);

private Funke:
  if (Not(Random(5)))
   CastObjects(SPRK,10,30,-1,-20);
  return(1);
