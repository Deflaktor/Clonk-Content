/*-- Laser-MG --*/

#strict
#include _WMM

IsWeapon:
  if(Local(8)==_AL2)
    return(ShortRangeWeapon()|MiddleRangeWeapon()|LongRangeWeapon());
  if(Local(8)==_AM0)
    return(ShortRangeWeapon()|MiddleRangeWeapon());
  return(ShortRangeWeapon());

public MinRange:
  return(10);

public MaxRange:
  if(Local(8)==_AL2)
    return(400);
  if(Local(8)==_AM0)
    return(350);
  return(100);

DPS:
  if(Local(8)!=-1&&Local(8))
    if(Local(8)==_AL1)
	  return(38*5*Dmg()/(GetActMapVal("Length", "Reload") * GetActMapVal("Delay", "Reload") + GetActMapVal("Length", "Schuss") * GetActMapVal("Delay", "Schuss")));
  return(_inherited());

DPA:
  if(Local(8)!=-1&&Local(8))
    if(Local(8)==_AL1)
      if(Local(9))
        return(5*Dmg()*Local(9));
  return(_inherited());
    
IsFiring:
  return(GetAction() S= "Schuss");
  
GetAmmoID:
  return(ExtractAmmunition(_AL2,_AL1,_AM0));

GetAmmoPacketID:
  return(FindAmmoPacket(_CEL,_LGP,_AP0));

GetAmmoNumber:
  return(CreateAmmo(50,50,50));

SelectionSound:
  Sound("WarmUpLaserMG");
  return(1);

ShotSound:
  return(1);

Fire:
  // Bereits beim flamen
  if (SEqual(GetAction(),"Schuss")) return(SetAction("Stop"));
  // Ammo suchen
  if (!SetVar(1,Contents())) return(CheckForAmmo());
  // Flamen
  if(ActIdle())
    SetAction("Schuss");
  return(1);

Shot:
  // Ammo abfeuern
  Exit(Par(0), Par(1)*28-14,-3+Random(6),0, 0,0,0 );
  ObjectCall(Par(0),"Launch",Par(1),this());
  return(1);

Schuss:
  // Träger
  SetVar(0,Contained());
  if(Contents(0,Contained())!=this()) return(SetAction("Stop"));
  if(Not(ObjectCall(Var(0),"ReadyToFire"))) return(SetAction("Stop"));
  if(Contained(Var(0))) return(SetAction("Stop"));
  if(!SetVar(1,Contents())) And(SetAction("Stop"),return(Sound("NoAmmo")));
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Var(0)),Var(1)); 
  // Richtung des Trägers abfragen
  SetVar(2,GetDir(Var(0)));
  if(!Shot(Var(1), Var(2), Var(0)))
    return(1);
  // Sound
  ShotSound();
  MunUpdate(Var(0));
  return(1);
