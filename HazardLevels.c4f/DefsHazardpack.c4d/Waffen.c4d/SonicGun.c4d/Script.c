#strict
#include _WOM

IsWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon());
public MinRange:
  return(10);

public MaxRange:
  return(300);

SelectionSound:
  Sound("Launch2");
  return(1);

ShotSound:
  Sound("Purge1");
  return(1);
  
/* Ammo ID */  
GetAmmoID:
  return(_AM4);
