#strict
#include _WMM

GetAmmoID:
  return(ExtractAmmunition(_HLS));

GetAmmoPacketID:
  return(FindAmmoPacket(_HLA));

GetAmmoNumber:
  return(CreateAmmo(3));

SelectionSound:
  Sound("Hot");
  return(1);

ShotSound:
  Sound("HotFireFlame");
  return(1);

public isWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon());

public MinRange:
  return(50);

public MaxRange:
  return(300);