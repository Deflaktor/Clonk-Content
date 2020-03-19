#strict
#include _WOM

SelectionSound:
  Sound("Drache");
  return(1);

ShotSound:
  Sound("Drachenodem");
  return(1);
  
/* Ammo ID */  
GetAmmoID:
  return(DA1D);

IsWeapon:
  return(MiddleRangeWeapon());

public MinRange:
  return(35);

public MaxRange:
  return(250);