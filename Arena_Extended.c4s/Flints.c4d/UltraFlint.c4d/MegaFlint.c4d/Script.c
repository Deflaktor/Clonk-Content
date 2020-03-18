#strict
#include PRNT

/*-- Mega-Flint --*/

Hit:
  Explode(200);
  return(1);
  
Check:
  SetAction("Delay");
  return(1);

Redefine:
  if(Contained())
    while(ScrollContents(Contained())!=this()) {}
  return(1);
  
Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);
