/*--- Kraftfeldgenerator ---*/
#strict
#include _WMM

GetAmmoID:
  return(ExtractAmmunition(_FFD,_BFD,_IFD));

GetAmmoPacketID:
  return(FindAmmoPacket(_CEL,_LGP,_AP0));

GetAmmoNumber:
  return(CreateAmmo(1,1,1));

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
  Exit(Par(0), Par(1)*24-12,0,0, 0,0,0 );
  ObjectCall(Par(0),"Launch",Par(1),this());
  // Sound
  ShotSound();
  // Nachladen
  SetAction("Target",Par(0));
  // Keine weiteren Aktionen machen
  return(0);

/* Feuern - Trägerbezogene Effekte lieber auf Activate */
Activate:
  // Abschalten
  if (SEqual(GetAction(),"Target")) return(Disactivate());
  Fire();
  return(1);

Disactivate:
  ObjectCall(GetActionTarget(),"Disactivate");
  Enter(this(),GetActionTarget());
  SetAction("Idle");
  return(1);

public Ammo:
  if(GetActionTarget()||Contents())
    return(1);
  return(0);
  
MunUpdate:
  if(Contents(0,Par(0))!=this())
    return(1);
  if(GetActionTarget())
    return(ObjectCall(GetActionTarget(),"MunUpdate"));
  if(Contents())
    return(ObjectCall(Contents(),"MunUpdate"));
  EnergyUpdate(Par(0),0);
  return(1);

EnergyUpdate:
  if(Contents(0,Par(0))!=this())
    return(1);
  SetPhysical("Magic",0,2,Par(0));
  DoMagicEnergy(0,Par(0));
  if(Local(1)==-1)
    return(1);
  SetPhysical("Magic",100000,2,Par(0));
  DoMagicEnergy(Par(1),Par(0));
  return(1);
