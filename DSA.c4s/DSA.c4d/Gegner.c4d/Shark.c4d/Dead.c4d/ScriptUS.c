/*-- Toter Hai --*/

#strict

/* Aktivierung */

/*public Activate:
  [Embowel]
  // Der Clonk soll dieses Objekt zerlegen, wenn er kann
  return (ObjectSetAction(Par(0),"Embowel",this()));*/

/* Wird zerlegt */

public Embowel:
  // In Bestandteile zerfallen
  Split2Components(this());
  return(1);

/* Verwesung */

private Decaying:
  DoCon(-4);
  return(1);
  
/* Aktionen von auﬂen */  
  
public Eat:
  ObjectCall(Par(0),"Feed",100);
  RemoveObject();
  return(1);
  