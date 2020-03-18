Initialize:
  SetAction("Timer");
  return(1);

Hit:
  Sound("RockHit*");
  Sound("MetalHit*");
  return(1);

End:
  RemoveObject();
  return(1);