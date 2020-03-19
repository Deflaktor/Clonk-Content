#strict
#include _WMM

public func IsWeapon() {
  return(ShortRangeWeapon());
}

public MinRange:
  return(10);

public MaxRange:
  return(150);

public func GetAmmoID() {
  return(ExtractAmmunition(_AM9));
}

public func GetAmmoPacketID() {
  return(FindAmmoPacket(_AP9));
}

public func GetAmmoNumber() {
  return(CreateAmmo(10));
}

public func SelectionSound() {
  Sound("Wheeng");
}

public func ShotSound() {
  Sound("Wheet");
}

/* Aktivierung (sich selber shrinken) */
public func Activate(object activator) {
  // Noch beim Nachladen
  if (GetAction() S= "Reload") return(0);
  // Ammo suchen
  var projectile = Contents();
  if (!projectile) return(CheckForAmmo());
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(activator),projectile); 
  // Ammo auf Träger abfeuern
  Exit(projectile, 0,0,0, 0,0,0 );
  ObjectCall(projectile,"HitObject",activator);
  // Sound
  ShotSound();
  // Nachladen
  SetAction("Reload");
  MunUpdate(activator); 
}