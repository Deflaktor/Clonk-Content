/*-- Wasserfass --*/

#strict

#include BARL

// Fassdaten
public func BarrelMaterial() { return(Material("Water")); }
public func BarrelMaterialName() { return("Water"); }

// Fassermittlungskette
global func GetBarrelType(iMaterial)
{
  if (iMaterial == Material("Water")) return(WBRL);
  return(_inherited(iMaterial));
}

// Verkauf
protected func CalcValue()
{
  // Bit 1 gesetzt: Fasswert 6
  if (BarrelConfiguration() & 1) return (inherited());
  // ansonsten 5
  return(5);
}

public func BarrelEject()
{
  // Inhaltsmenge ermitteln
  var wamnt = iFillLevel, obj, fExt;
  // Objekte im Umkreis löschen
  while (obj = FindObject(0, -20, -15, 40, 30, OCF_OnFire(), 0,0, NoContainer(), obj))
    if (Random(wamnt*3) > GetMass(obj))
    {
      fExt=1; Extinguish(obj);
    }
  // Geräusche
  if (fExt) Sound("Extinguish");
  Sound("Splash1");
  return(_inherited());
}

