CheckTemp:
  if ( GreaterThan( GetTemperature(), 0 ) )
    Call("Melt");
  return(1);
Hit:
  Sound("RockHit*");
  return(1);
Melt:
  DoCon(-2);
  CastPXS("Water",4,0);
  return(1);
