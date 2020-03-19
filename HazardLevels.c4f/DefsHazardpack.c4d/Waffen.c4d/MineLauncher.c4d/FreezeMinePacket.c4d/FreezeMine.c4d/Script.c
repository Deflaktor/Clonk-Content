/*-- Eismine --*/

#strict
#include _AM8

BlowUp:
  Sound("freeze");
  ObjectSetAction(Par(0),"Frozen");
  RemoveObject();
  return(1);