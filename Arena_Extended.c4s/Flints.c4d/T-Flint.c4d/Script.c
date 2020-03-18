#strict
#include PRNT

/*-- T-Flint --*/

/* Aufschlag */

NoShiftOwner:
  return(!(GetAction()S="Idle"));

Hit:
  Sound("RockHit*");
  if (Not(ActIdle())) return(1);
  Sound("Fuse");
  SetAction("Activated");
  return(1);

private BlowUp:
  Explode(20);
  return(1);

Activate:
  Hit();
  return(1);
  
/* Produkteigenschaften */

public IsChemicalProduct: return(1);

/* Forschung */

public GetResearchBase: return(0);