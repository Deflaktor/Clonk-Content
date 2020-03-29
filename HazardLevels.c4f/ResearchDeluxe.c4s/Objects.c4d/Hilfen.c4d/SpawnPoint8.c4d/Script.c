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
  if(!Global(33)&&!Local(3)&&!FindObject(MEN1)&&Global(9764))
  {
  if(Local(0)==_FFM)
  return(RemoveObject());
  CreateContents(RandomID());
  AutoSetType();
  SetLocal(3,1);
  return(1);
  }
  if(!Global(33)&&!Local(3)) return(1);

  // Kein Typ definiert
  if (Not(Local(0))) return(0);
  // Objekt ist noch im Einsatz
  if (Local(1)) return( SetLocal(2,30) );
  // Verzögerung abwarten
  if (Local(2)) return(SetLocal(2,Sum(Local(2),-1)));
  // Objekt erzeugen und Pointer auf das Objekt merken
  Exit(SetLocal(1,CreateContents(Local(0))));
  // Effekt
  if(!Contained())
  CastObjects(SPRK,10,10,0,-5);
  return(1);

SpawnRandomID:
  CreateContents(RandomID());
  AutoSetType();
  return(1);
  
RandomID:
var i = Random(14);
if (i==0)
  return(_BLZ);
if (i==1)
  return(LGP2);
if (i==2)
  return(_EGW);
if (i==3)
  return(_WP3);
if (i==4)
  return(_HLR);
if (i==5)
  return(HLS_);
if (i==6)
  return(_WMW);
if (i==7)
  return(MINI);
if (i==8)
  return(_WP8);
if (i==9)
  return(_PR4);
if (i==10)
  return(_WP2);
if (i==11)
  return(_SR4);
if (i==12)
  return(_SLG);
if (i==13)
  return(_WP9);
return(RandomID());