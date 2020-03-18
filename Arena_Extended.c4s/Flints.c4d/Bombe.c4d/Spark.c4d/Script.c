/*-- Funke --*/

private Process:
  if (Or( GreaterThan(GetActTime(),15), Not(Random(4)) )) 
    RemoveObject();
  return(1);

protected Initialize:
  SetAction("Sparkle");
  return(1);
