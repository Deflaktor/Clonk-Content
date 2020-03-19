#strict
#include _WOM

SelectionSound:
  Sound("Launch2");
  return(1);

ShotSound:
  Sound("Blast3");
  return(1);
  
/* Ammo ID */  
GetAmmoID:
  return(_KTA);

Shot:
  // Ammo abfeuern
  Exit(Par(0), Par(1)*40-20,8,0, 0,0,0 );
  ObjectCall(Par(0),"Launch",Par(1));
  return(1);

IsWeapon:
  return(LongRangeWeapon());

public MinRange:
  return(200);

public MaxRange:
  return(800);