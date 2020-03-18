#strict

Initialize:
  SetAction("Timer");
  return(1);

Hit:
  Sound("god");
  // Remove();
  return(1);

Activate:
  Remove();
  return(1);

Remove:
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  RemoveObject();
  return(1);