#strict
#include _WOM

SelectionSound:
  Sound("IceCharge");
  return(1);

ShotSound:
  Sound("IceShot");
  return(1);
  
/* Ammo ID */  
GetAmmoID:
  return(_EGM);

IsWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon()|LongRangeWeapon());

public MinRange:
  return(5);

public MaxRange:
  return(350);