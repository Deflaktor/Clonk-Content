#strict


Initialize:
  SetAction("Undefined");
  return(1);

AutoSetType:
  // Um einen Typ automatisch zu setzen, einfach das zu
  // erzeugende Objekt als in den SpawnPoint verschieben
  SetLocal(0,GetID(Contents()));
  SetAction("Set");
  Message("Set to|%i",this(),Local(0));
  RemoveObject(Contents());
  Sound("SpawnPointSet");
  return(1);
  
SetType:
  SetLocal(0,Par(0));
  SetAction("Set");
  if(!Local(1)) {
    Message("Set to|%i",this(),Local(0));
    Sound("SpawnPointSet");
  }
  return(1);
EnterIt:
  Enter(this(),FindObject(0,0,0,-1,-1));
  SetLocal(1);
  return(1);
  
IsSpawnPoint:
  return(1);

Timer:
  // Typ automatisch setzen
  if (Contents()) AutoSetType();
  // Kein Typ definiert
  if (Not(Local(0))) return(0);
  // Objekt ist noch im Einsatz
  if (Local(1)) return( SetLocal(2,30) );
  // Verzögerung abwarten
  if (Local(2)) return(SetLocal(2,Sum(Local(2),-1)));
  // Objekt erzeugen und Pointer auf das Objekt merken
  Exit(SetLocal(1,CreateContents(Local(0))));
  if(Local(3))
    Enter(Local(3),Local(1));
  else
  // Effekt
  CastObjects(SPRK,10,20,0,-5);
  return( SetLocal(2,30) );
  
