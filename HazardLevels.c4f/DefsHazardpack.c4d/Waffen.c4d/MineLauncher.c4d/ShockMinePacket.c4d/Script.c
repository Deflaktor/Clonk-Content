#strict
#include _MOV

/* Per Doppelklick auf Graben in Komponenten zerlegen */
Activate:
  SetOwner(GetOwner(Par(0)));
  Split2Components(this());
  Sound("Connect");
  return(1);
