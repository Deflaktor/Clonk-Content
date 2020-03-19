/*-- Lavafass --*/

#strict

#include BARL

// Fassdaten
public func BarrelMaterial() { return(Material("Lava")); }
public func BarrelMaterialName() { return("Lava"); }

// Fassermittlungskette
global func GetBarrelType(iMaterial)
{
  if (iMaterial == Material("Lava")) return(LBRL);
  if (iMaterial == Material("DuroLava")) return(LBRL);
  return(_inherited(iMaterial));
}