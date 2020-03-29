
#strict
#appendto _SP2
#appendto _SP3

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
  if(Contained())
  SetLocal(1,CreateContents(Local(0),Contained()));
  if(!Contained())
  SetLocal(1,CreateObject(Local(0)));
  // Effekt
  if(!Contained())
  CastObjects(SPRK,10,10,0,-5);
  return(1);