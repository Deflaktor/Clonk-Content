/*-- Neues Objekt --*/

#strict

// Local(0): Target
// Local(1): Erzeuger der Unsichtbarkeit (Kraftfeld)
// Local(2): Distance
// Local(68,Par(0)): SetInvisible Flag
// Local(3): Flag to check Local(5) on target

protected Initialize:
  SetLocal(68,Local(1));
  return(1);

Catch:
  SetVisibility(VIS_Owner() | VIS_God(), Par(0));
  SetClrModulation(RGBa(255,255,255,127), Par(0));
  SetLocal(68,Local(1),Par(0));
  return(1);

Release:
  SetVisibility(VIS_All(), Par(0));
  SetClrModulation(RGBa(255,255,255,0), Par(0));
  SetLocal(68,0,Par(0));
  RemoveObject();
  return(1);

Help:
  if(!Local(0))
    RemoveObject();
  if(Local(0))
    Catch(Local(0));
  if(Distance(GetX(Local(1)), GetY(Local(1)), GetX(Local(0)), GetY(Local(0)))>Local(2))
    Release(Local(0));
  if(GetAction(Local(1)) eq "Idle")
    Release(Local(0));
  if(!Local(1))
    Release(Local(0));
  else if(!Local(5,Local(1))&&Local(3))
    Release(Local(0));
  return(1);