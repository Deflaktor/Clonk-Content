#strict
#include _WOM

SelectionSound:
  Sound("Discharge");
  return(1);

ShotSound:
  Sound("Blast3");
  RemoveObject();
  return(1);
  
/* Ammo ID */  
GetAmmoID:
  return(__NR);

IsWeapon:
  return(LongRangeWeapon());

public MinRange:
  return(300);

public MaxRange:
  return(800);