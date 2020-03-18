/*-- Neues Objekt --*/

#strict
#include PRNT

protected Initialize:
  return(1);

Hit:
  CastObjectsX(BANE,1,60-Random(30),0,-10,270,45,"Sett");
  CastObjectsX(BANE,1,60-Random(30),0,-10,270,45,"Sett");
  CastObjectsX(BANE,1,60-Random(30),0,-10,270,45,"Sett");
  Explode(30);
  Explode(15);
  return(1);

Sett:
  ObjectSetAction(Par(0),"Checking");
  SetOwner(GetOwner(), Par(0));
  return(1);