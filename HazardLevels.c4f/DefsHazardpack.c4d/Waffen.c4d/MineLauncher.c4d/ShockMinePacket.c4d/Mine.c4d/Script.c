#strict
#include _AM8

BlowUp:
  SetLocal(0,CreateObject(SWE2));
  ObjectSetAction(Local(0),"Implode");
  return(RemoveObject(this()));
  
Dmg:
  return(1*30);
