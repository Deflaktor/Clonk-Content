#strict

Hit:
  Sound("RockHit*");
  Sound("MetalHit*");
  return(1);

Decay:
  SetLocal(0,Sum(Local(0),+1));
  if (GreaterThan(Local(0),45)) RemoveObject();
  return(1);