#strict

Initialize:
  
  return(1);


Hit:
  Sound("RockHit*");
  return(1);

Damage:
  if ( LessThan( GetDamage(), 30 ) ) return(0);
  // Crack open
  while (Contents()) Exit(Contents());
  CastObjects(_CF1,1,20,0,-10);
  CastObjects(_CF2,5,20,0,-10);
  Sound("CrateCrack");
  Sound("Blast2");
  RemoveObject();  
  return(1);