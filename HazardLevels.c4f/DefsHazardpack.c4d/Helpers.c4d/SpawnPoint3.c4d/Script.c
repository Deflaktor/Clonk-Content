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
  CastObjects(Local(0),10,40);
  // Effekt
  CastObjects(SPRK,10,10,0,-5);
  return( SetLocal(2,30) );
  
