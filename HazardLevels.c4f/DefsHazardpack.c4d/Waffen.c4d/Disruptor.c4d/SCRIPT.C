#strict
#include _WMM

IsWeapon:
  return(MiddleRangeWeapon()|LongRangeWeapon());

public MinRange:
  return(35);

public MaxRange:
  return(350);

GetAmmoID:
  return(ExtractAmmunition(RAM1,RAM7));

GetAmmoPacketID:
  return(FindAmmoPacket(RAP1,_AP7));

GetAmmoNumber:
  return(CreateAmmo(3,3));

SelectionSound:
  Sound("DisruptorCharge");
  return(1);

ShotSound:
  Sound("DisruptorFire");
  return(1);
