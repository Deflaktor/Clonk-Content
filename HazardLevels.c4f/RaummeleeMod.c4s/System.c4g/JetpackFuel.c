/*-- Neues Script --*/

#strict
#appendto _AP3

Activate:
  SetLocal(1,1000,Par(0));
  Sound("Energize");
  RemoveObject();
  return(1);
