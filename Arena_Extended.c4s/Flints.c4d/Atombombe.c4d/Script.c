/*-- Neues Objekt --*/

#strict
#include PRNT

NoShiftOwner:
  return(!(GetAction()S="Idle"));

Initialize:
  return(1);

Hit:
  Sound("RockHit*");
  if(!ActIdle()) return(1);
  SetAction("Activated");
  return(1);


BlowUp:
  SetVar(0,CreateObject(NEBB,0,0,GetOwner()));
  ObjectCall(Var(0),"BlowUp");
  return(RemoveObject());  