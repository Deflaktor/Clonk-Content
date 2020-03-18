#strict
#appendto LNKT


/* Verbinden zweier Gebäude mit einer Leitung */
private func ConnectLine(line, to)
{
  var t1 = GetActionTarget(0, line);
  if(t1 == this() ) { t1 = GetActionTarget(1, line); }
  
  if(GetID(line)==PWR2 && GetID(to)!=ELEV) {
    if(GetID(to)!=DYNM||GetID(t1)!=ELEV) {
      Sound("Error");
      Message("%s kann nur an|Fahrstühlen angeschlossen werden.", this(), GetName(line));
      return(0);
	}
  } else if(GetID(to)==DYNM) {
    Sound("Error");
    Message("%s kann nicht an|%s angeschlossen werden.", this(), GetName(line), GetName(to));
    return(0);
  }
  
  return(_inherited(line, to));
}