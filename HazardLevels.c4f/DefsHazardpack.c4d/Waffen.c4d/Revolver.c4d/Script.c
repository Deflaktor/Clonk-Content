#strict
#include _WOM

IsWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon());

public MinRange:
  return(5);

public MaxRange:
  return(200);

Hit:
  Sound("MetalHit*");
  return(1);

SelectionSound:
  Sound("Load");
  return(1);

ShotSound:
  Sound("PFire*");
  CreateObject(WAPH)->Start(GetDir(Contained()));
  return(1);
  
/* Ammo ID */  
GetAmmoID:
  return(_BUL);

