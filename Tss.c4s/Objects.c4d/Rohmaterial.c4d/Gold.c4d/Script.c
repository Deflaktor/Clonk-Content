/*-- Gold --*/

#strict

/* Aufschlag */

protected func Hit()
{
  Sound("RockHit*");
  return(1);
}

func IsAlchemContainer() { return(true); }
func AlchemProcessTime() { return(180); }

/* Kann in der Chemiefabrik hergestellt werden */
public func IsChemicalProduct() { return(1); }
