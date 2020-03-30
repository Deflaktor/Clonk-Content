#strict

protected Initialize:
  SetAction("Decay");
  return(1);

protected Remove:
  CastPXS("Blood", 20, 20);
  return(RemoveObject());

protected Hit:
  // Sound("MeatHit");
  CastPXS("Blood", 10, 20);
  SetXDir(-2);
  SetRDir(2);
  return(1);