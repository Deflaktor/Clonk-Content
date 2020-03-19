/*-- Granaten-Pack --*/

#strict
#include _MOV

/* Per Doppelklick auf Graben in Einzelgranaten zerlegen */
Activate:
  Split2Components(this());
  Sound("Connect");
  return(1);
