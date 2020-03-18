/*-- Brandbombe --*/

/* Aufschlag */

protected Hit:
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Sound("Inflame");
  Sound("Fuse");
  RemoveObject();
  return(1);