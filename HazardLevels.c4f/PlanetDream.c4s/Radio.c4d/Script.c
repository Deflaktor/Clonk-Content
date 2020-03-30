/*--- Teleporter ---*/
#strict
#include _WMM

GetAmmoID:
  return(ExtractAmmunition(DFSH));

GetAmmoPacketID:
  return(FindAmmoPacket(_CEL));

GetAmmoNumber:
  return(CreateAmmo(1));

SelectionSound:
  Sound("Magic*");
  return(1);

ShotSound:
  Sound("Magic*");
  return(1);

/* Objekt keine Waffe (auch wegen WalkArmed/Unarmed) */
IsWeapon:
  return(0);

Shot:
  // Ammo abfeuern
  SetOwner(-1,Par(0));
  RemoveObject(Par(0));
  // Sound
  ShotSound();
  SetPosition(1420,200,Par(2));
  return(0);

/* Feuern - Trägerbezogene Effekte lieber auf Activate */
Activate:
  Fire();
  return(1);

