/*-- Splitter --*/

#strict
#include PRNT

Initialize:
  SetAction("Delay");
  return(1);

protected Hit:
 Explode(10);
return(1);

Decay:
  SetLocal(0,Sum(Local(0),+1));
  if (GreaterThan(Local(0),30)) RemoveObject();
 return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(GetOwner(Var(0))!=GetOwner()) Hit();
  return(1);
