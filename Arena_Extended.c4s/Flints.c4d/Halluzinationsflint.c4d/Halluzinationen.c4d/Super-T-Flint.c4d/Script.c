/*-- Super-T-Flint --*/

protected Hit:
  Sound("RockHit*");
  if(Not(ActIdle())) return(1);
  Sound("Fuse");
  SetAction("Activated");
  return(1);

private BlowUp:
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  RemoveObject();
  return(1);
