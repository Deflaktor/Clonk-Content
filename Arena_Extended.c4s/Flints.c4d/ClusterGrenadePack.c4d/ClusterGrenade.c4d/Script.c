/*-- Clustergrenade --*/

#strict
#include PRNT

/* Aufschlag */
Hit:
 CastObjectsX(_SPL,4,60,0,-10,270,360,"Sett");
 Explode(10);
return(1);

/* Wird abgefeuert */
Launch:  
  // Sicht verfolgen
  SetPlrView(GetOwner(),this());
  return(1);

Sett:
  ObjectSetAction(Par(0),"Checking");
  SetOwner(GetOwner(), Par(0));
  return(1);