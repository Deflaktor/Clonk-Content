/* Schwere KI */

#strict
#include KIL1

Initialize:
  _inherited();
  SetWeapID(GameCall("Zufallsflint2"));
  SetColorDw(RGBa(255,0,0,0));
  SetClrModulation(RGBa(170,50,50,0));
  SetPhysical("Walk",40000,2);
  return(1);
