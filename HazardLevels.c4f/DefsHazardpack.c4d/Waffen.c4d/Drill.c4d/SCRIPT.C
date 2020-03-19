#strict
#include _WOM

SelectionSound:
  Sound("Launch2");
  return(1);

ShotSound:
  Sound("ShotShot");
  return(1);
  
/* Ammo ID */  
GetAmmoID:
  return(_DS6);
  
IsWeapon:
  return(ShortRangeWeapon());

public MinRange:
  return(10);

public MaxRange:
  return(150);