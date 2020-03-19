#strict
#include _WOM

SelectionSound:
  Sound("Sword");
  return(1);

ShotSound:
  Sound("SwordShot");
  return(1);

public isWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon()|LongRangeWeapon());

public MinRange:
  return(5);

public MaxRange:
  return(400);

/* Ammo ID */  
GetAmmoID:
  return(GBK2);

