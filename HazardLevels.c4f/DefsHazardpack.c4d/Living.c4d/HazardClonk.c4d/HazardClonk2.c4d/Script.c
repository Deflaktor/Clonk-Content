/*-- HazardClonk mit Gravity-Suit --*/

#strict
#include HZCK

protected ContactBottom:
  if (Not(SEqual(GetAction(),"Swim"))) return(0);
  SetAction("Walk");
  return(1);

/* Initialisierung */  
Init:
  SetPhysical( "Swim", GetPhysical("Swim",1)/100*130, 2 );
  SetPhysical( "Breath", GetPhysical("Breath",1)*2, 2 );
  SetAction("Walk");
  return(1);
