/*-- Neues Objekt --*/

#strict

local reloadTime, reloading;

// --- Customize ---

GetAmmoID:
  return(0);

SelectionSound:
  Sound("Purge2");
  return(1);

ShotSound:
  Sound("Purge1");
  return(1);
  
DPS:
  return(38*Dmg()/(GetActMapVal("Length", "Reload") * GetActMapVal("Delay", "Reload")));

Dmg:
  return(DefinitionCall(GetAmmoID(), "Dmg"));
  
NeedsAmmo:
  return(0);
  
Shot:
  // Ammo abfeuern
  Exit(Par(0), Par(1)*24-12,0,0, 0,0,0 );
  ObjectCall(Par(0),"Launch",Par(1));
  return(1);

// --- Customize Ende ---


Fire:
  // Noch beim Nachladen
  if (!ActIdle()) return(0);
  // Träger
  SetVar(0,Contained());
  // Ammo suchen
  if (!SetVar(1,Contents()))
    // Ammo erstellen
    if (SetVar(1,CreateContents(GetAmmoID())))
      // Besitzer des Projektils setzen
      SetOwner(GetOwner(Var(0)),Var(1)); 
  // Richtung des Trägers abfragen
  SetVar(2,GetDir(Var(0)));
  if(!Shot(Var(1), Var(2), Var(0)))
    return(0);
  // Sound
  ShotSound();
  // Nachladen
  SetAction("Reload");
  reloadTime=GetActMapVal("Length", "Reload") * GetActMapVal("Delay", "Reload");
  reloading = reloadTime;
  return(1);

/* Objekt wurde ausgewählt */
public Selection:
  MunUpdate(Contained());
  SelectionSound();
  return(1);

Collection:
  MunUpdate(Contained());
  return(1);

/* Objekt ist eine Waffe */
public IsWeapon:
  return(ShortRangeWeapon());

/* Objekt Munition */
public MaxAmmo:
  return(-1);

MunUpdate:
  if(Not(Contents(0,Contained())==this()))
    return(1);
  SetPhysical("Magic",0,2,Par(0));
  DoMagicEnergy(0,Par(0));
  SetPhysical("Magic",100000,2,Par(0));
  DoMagicEnergy(-reloading*100/reloadTime+100,Par(0));
  return(1);

/* TimerCall! Aktuallisiert Magie-Anzeige des Trägers */
Reloaden:
  if(!Random(10)) if(GBackSolid(0,0)) if(GBackLiquid(0,-2)) SetPosition(GetX(),GetY()-1);
  if(!reloadTime)
    reloadTime=GetActMapVal("Length", "Reload") * GetActMapVal("Delay", "Reload");
  reloading--;
  if(reloading<0)
    reloading=0;
  MunUpdate(Contained());
  return(1);
