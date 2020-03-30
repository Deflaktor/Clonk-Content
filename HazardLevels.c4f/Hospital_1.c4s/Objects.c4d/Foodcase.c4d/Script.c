Hit:
  Sound("MetalHit*");
  return(1);

Activate:
  DoEnergy(+10,Par(0));
  Sound("ClonkMunch");
  RemoveObject();
  return(1);

