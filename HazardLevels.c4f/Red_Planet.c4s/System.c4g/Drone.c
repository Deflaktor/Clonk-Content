#strict

#appendto _DRN

private MoveToNextWaypoint:
  // Nächsten Waypoint suchen
  if (Equal(Local(0),0)) SetVar(0,FindObject(WAY1,0,1,-1,-1));  
  if (Equal(Local(0),1)) SetVar(0,FindObject(WAY2,0,1,-1,-1));  
  if (Equal(Local(0),2)) SetVar(0,FindObject(WAY3,0,1,-1,-1));  
  // Kein Waypoint gefunden
  if (Not(Var(0))) return(0);
  // Stoppen
  SetXDir(0);
  SetYDir(0);
  // Kommando setzen
  SetCommand(this(),"MoveTo",Var(0));
  // Wegpunkt weiterzählen
  SetLocal(0,Sum(Local(0),+1));
  if (GreaterThan(Local(0),2)) SetLocal(0,0);
  return(1);
