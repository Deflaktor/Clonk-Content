SmokeTrail:
  Smoke(0,0,5);
  Smoke(0,-5,Random(7));
  if (GreaterThan( GetActTime(), 75 )) Call("Hit");
  return(1);
Completion:
  SetAction("Evaporate");
  return(1);
Hit:
  CastPXS("Lava",50,35);
  AssignRemoval();
  return(1);
