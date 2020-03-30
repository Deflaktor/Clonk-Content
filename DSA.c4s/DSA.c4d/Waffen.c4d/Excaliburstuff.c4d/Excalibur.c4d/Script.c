Initialize:
  SetAction("Ready");
  return(1);

Hit:
  Sound("SwordHit*");
  return(1);

// Basis schaden den der Gegner erleidet * "Fight" Attribut / 100000
Power:
  return(10);

// Rate in % für Critical Hit (Der Gegner fliegt weg + doppelter Schaden)
CritRate:
  return(30);

// Speed - wie kleiner umso besser (Wie lange warten, bis nächste Schlag kommen kann)
Speed:
  return(2);

ControlThrow:
  if(SEqual(GetAction(Contained()),"Walk")) if(GreaterThan(Local(0),2)) if(SEqual(GetAction(),"Ready")) Call("DuDarfst");
  if(SEqual(GetAction(Contained()),"Swim")) if(GreaterThan(Local(0),2)) if(SEqual(GetAction(),"Ready")) Call("DuDarfst");
  if(SEqual(GetAction(Contained()),"Jump")) if(GreaterThan(Local(0),2)) if(SEqual(GetAction(),"Ready")) Call("DuDarfst");
  return(1);

DuDarfst:
  SetAction("Warten");
  if(Not(Equal(GetID(Contained()),KR3A))) Call("blablabla");
  if(Equal(GetID(Contained()),KR3A)) Call("weitergehts");
  return(1);

weitergehts:
  SetLocal(0,Sum(Local(0),-2));
  CreateObject(BS3A,0,0,-1);
  return(1);

Activate:
  if(SEqual(GetAction(Contained()),"Verteidigen")) ObjectSetAction(Contained(),"Walk");
  if(GreaterThan(Local(0),30)) if(SEqual(GetAction(),"Ready")) Call("Abwehrgehtlos");
  return(1);

Abwehrgehtlos:
  if(Not(Equal(GetID(Contained()),KR3A))) Call("blablabla");
  if(Equal(GetID(Contained()),KR3A)) ObjectSetAction(Contained(),"Verteidigen");
  SetLocal(1,this(),Contained());
  return(1);

Destroy:
  RemoveObject(Par(0));
  CreateObject(DT3A,Sub(GetX(Par(0)),GetX()),Sub(GetY(Par(0)),GetY()),GetOwner(Par(0)));
  SetLocal(0,Sum(Local(0),-1));
  return(1);

SonnenLicht:
  if(LessThan(Local(0),1)) SetLocal(0,Sum(Local(0),1));
  //Log("Sonnenenergie von Excalibur: %d",Local(0));
  return(1);

blablabla:
  Message("Nur für Krieger!");
  return(1);

ControlLeft:
  if (SEqual(GetAction(Par(0)),"Verteidigen"))    return(SetDir(DIR_Left(),Par(0)));
  return(0);
ControlRight:
  if (SEqual(GetAction(Par(0)),"Verteidigen"))    return(SetDir(DIR_Right(),Par(0)));
  return(0);
ControlRightDouble:
  if (AmVerteidigen())    And( ObjectCall( Par(0), "StopAiming" ), SetComDir(COMD_Right(),Par(0)) );
  return(0);
ControlLeftDouble:
  if (AmVerteidigen())    And( ObjectCall( Par(0), "StopAiming" ), SetComDir(COMD_Left(),Par(0)) );
  return(0);

AmVerteidigen:
  return (SEqual( GetAction(Contained()),"Verteidigen" ));