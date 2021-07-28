#strict
#include PRNT

Redefine:
  if(Contained())
    while(ScrollContents(Contained())!=this()) {}
  return(1);

Hit:
  CreateObject(_FLF,0,0,GetOwner())->Launch();
  RemoveObject();
  return(1);

Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);
