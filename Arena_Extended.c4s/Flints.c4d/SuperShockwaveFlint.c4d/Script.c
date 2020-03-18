#strict
#include PRNT

Hit:
  SetLocal(0,CreateObject(SWE3,0,0,GetOwner()));
  ObjectSetAction(Local(0),"Implode");
  return(RemoveObject());

Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);
