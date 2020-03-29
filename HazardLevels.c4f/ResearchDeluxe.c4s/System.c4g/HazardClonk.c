#strict
#appendto HZCK
#appendto HCK2
#appendto HCK3
#appendto HCK4

static primaryObjective, secondaryObjective, cardObjective1, cardObjective2, cardObjective3, cardObjective4, cardObjective5, optionalObjective;

Death:
  if(!Global(340)) return(_inherited());
  // Sound und Meldung
  Sound("Die");
  SetAlive(0);
  // Irgendwo drin? Raus da!
  while(Contained())
    Exit();
  // Etwas in dir? Raus damit!
  while(SetVar(0,Contents())) Exit(Var(0),0,0,Random(360),GetXDir(),GetYDir());
  // Spieler nicht eliminieren, aber Handlungsunfähig machen
  MakeCrewMember(this(),GetOwner());
return(1);
  

/* Kontext */

// ---- Optional Objectives ----

public func ContextOptionalObjective(pCaller)
{
  //[Optionales Ziel|Image=MCM3|Condition=HasOptionalObjective]
  [Sekundärziel|Image=MCM2|Condition=HasOptionalObjective]
  HasOptionalObjective()->Trigger();
  return(1);
}

HasOptionalObjective:
  return(optionalObjective);

// ---- ID Card Objectives ----
    
public func ContextCardObjective4(pCaller)
{
  [Gelbe Zugangskarte|Image=RDC4|Condition=HasCardObjective4]
  HasCardObjective4()->Trigger();
  return(1);
}

HasCardObjective4:
  return(cardObjective4);

public func ContextCardObjective3(pCaller)
{
  [Grüne Zugangskarte|Image=RDC3|Condition=HasCardObjective3]
  HasCardObjective3()->Trigger();
  return(1);
}

HasCardObjective3:
  return(cardObjective3);

public func ContextCardObjective5(pCaller)
{
  [Weiße Zugangskarte|Image=RDC5|Condition=HasCardObjective5]
  HasCardObjective5()->Trigger();
  return(1);
}

HasCardObjective5:
  return(cardObjective5);

public func ContextCardObjective2(pCaller)
{
  [Rote Zugangskarte|Image=RDC2|Condition=HasCardObjective2]
  HasCardObjective2()->Trigger();
  return(1);
}

HasCardObjective2:
  return(cardObjective2);

public func ContextCardObjective1(pCaller)
{
  [Blaue Zugangskarte|Image=_RDC|Condition=HasCardObjective1]
  HasCardObjective1()->Trigger();
  return(1);
}

HasCardObjective1:
  return(cardObjective1);
  
// ---- Secondary and Primary Objectives ----
  
public func ContextSecondaryObjective(pCaller)
{
  [Sekundärziel|Image=MCM2|Condition=HasSecondaryObjective]
  HasSecondaryObjective()->Trigger();
  return(1);
}

HasSecondaryObjective:
  return(secondaryObjective);

public func ContextPrimaryObjective(pCaller)
{
  [Primärziel|Image=MCM1|Condition=HasPrimaryObjective]
  HasPrimaryObjective()->Trigger();
  return(1);
}


public func ContextPickup(pCaller)
{
  [Extraction beantragen|Image=MI_P]
  return(_inherited());
}


public func ContextInfo(pCaller) 
{
  [Objektinfo|Image=INFO]
  return(_inherited());
}


public func ContextStatus(pCaller)
{
  [Status|Image=MI_P]
  return(_inherited());
}

HasPrimaryObjective:
  return(primaryObjective);