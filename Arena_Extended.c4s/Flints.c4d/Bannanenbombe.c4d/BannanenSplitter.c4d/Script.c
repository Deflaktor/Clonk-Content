/*-- Neues Objekt --*/

#strict
#include PRNT

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);
  
Hit:
  Explode(30);
  Explode(15);
  return(1);