#strict
#include PRNT


NoShiftOwner:
  return(!(GetAction()S="Idle"));


Hit:
  Sound("RockHit*");
  if (Not(ActIdle())) return(1);
  Sound("Fuse");
  SetAction("Activated");
  return(1);

Redefine:
  if(Contained())
    while(ScrollContents(Contained())!=this()) {}
  return(1);
  
BlowUp:
  SetLocal(0,CreateObject(SWE7,0,0,GetOwner()));
  ObjectSetAction(Local(0),"Implode");
  return(RemoveObject());

Activate:
  Hit();
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);
