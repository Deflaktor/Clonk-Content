/*-- Der Clonk --*/

#strict

local obj,e;

/* Initialisierung */

protected Initialize:
  SetAction("Blowing");
  return(1);

Init:
  obj=Par(0);
  return(1);

BlowUp:
  if(e>20)
    Call("Ende");
  DoCon(+4);
  Sound("Gear");
  e++;
  return(1);

Ende:
  SetVar(0,FindContents(CLON));
  Exit(Var(0));
  Kill(Var(0));
  RemoveObject();
  return(1);