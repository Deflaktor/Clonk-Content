/*-- Ölfass --*/

#strict

#include BARL

// Fassdaten
public func BarrelMaterial() { return(Material("Oil")); }
public func BarrelMaterialName() { return("Oil"); }

// Fassermittlungskette
global func GetBarrelType(iMaterial)
{
  if (iMaterial == Material("Oil")) return(OBRL);
  return(_inherited(iMaterial));
}

protected func Damage()
{
  CastObjects(DFLM, GetComDir() / 12, 15);
  CreateContents(BARL);
  Exit(Contents(), 0, 0, Random(360), Random(7) - 3, Random(3) - 8, +10);
  RemoveObject();
  ObjectCall(CreateObject(EXPL),"Launch", Max(GetComDir() / 6, 15));
  return(1);
}  

