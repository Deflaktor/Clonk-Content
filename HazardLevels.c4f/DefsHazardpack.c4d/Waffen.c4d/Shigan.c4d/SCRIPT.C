#strict
#include _WOM

IsWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon());

public MinRange:
  return(10);

public MaxRange:
  return(200);
  
SelectionSound:
  Sound("Launch2");
  return(1);

ShotSound:
  Sound("ShotShot");
  return(1);
  
/* Ammo ID */  
GetAmmoID:
  return(C_S5);
