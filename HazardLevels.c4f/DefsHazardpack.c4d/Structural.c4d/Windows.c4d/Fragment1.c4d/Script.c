#strict

Hit:
  Sound("MetalHit*");
  return(1);

Decay:
  if(Local(1)) return(1);
  SetLocal(0,Sum(Local(0),+1));
  if (GreaterThan(Local(0),25)) RemoveObject();
  return(1);