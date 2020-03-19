/*-- Eisminen-Pack --*/
#include _MOV
#strict

/* Per Doppelklick auf Graben in Komponenten zerlegen */
Activate:
  Split2Components(this());
  Sound("Connect");
  return(1);
