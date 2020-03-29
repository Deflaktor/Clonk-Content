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
/*  if (!FindObject(MEN1))
  return(RemoveObject()); */
  if(Global(3)==0||Global(3)==1||Global(3)==2)
  return(1);
  // Kein Typ definiert
  if (Not(Local(0))) return(0);
  if(Contained())
  SetLocal(1,CreateContents(Local(0),Contained()));
  if(!Contained())
  SetLocal(1,CreateObject(Local(0)));
  // Effekt
  if(!Contained())
  CastObjects(SPRK,10,10,0,-5);
  return(RemoveObject());
