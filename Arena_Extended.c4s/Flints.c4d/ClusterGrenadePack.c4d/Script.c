/*-- Clustergranaten-Pack --*/

#strict
#include PRNT

/* Per Doppelklick auf Graben in Einzelgranaten zerlegen */
Departure:
  SetVar(0);
  while(Var(0)<9)
{
  SetVar(1,CreateObject(_CGM,Var(0)%3-1,Var(0)/3-1, GetOwner()));
  SetXDir(GetXDir()+Var(0)%3-1,Var(1));
  SetYDir(GetYDir()+Var(0)/3-1,Var(1));
  SetVar(0,Var(0)+1);
}
  Sound("Connect");
  return(RemoveObject());

Hit:
Explode(40);
return(1);