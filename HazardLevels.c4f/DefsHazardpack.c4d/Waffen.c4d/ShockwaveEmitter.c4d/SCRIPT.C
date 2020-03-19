#strict
#include _WMM

GetAmmoID:
  return(ExtractAmmunition(_SWS,_FLE,_QSG));

GetAmmoPacketID:
  return(FindAmmoPacket(_CEL,_LGP,_AP0));

GetAmmoNumber:
  return(CreateAmmo(1,1,1));

SelectionSound:
  Sound("TOOK");
  return(1);

ShotSound:
  Sound("TOOK");
  return(1);

IsWeapon:
  return(LongRangeWeapon());

public MinRange:
  return(200);

public MaxRange:
  return(600);