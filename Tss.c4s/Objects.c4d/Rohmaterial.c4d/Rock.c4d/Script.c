/*--- Der Stein ---*/

#strict

protected func Hit()
{
  Sound("RockHit*");
  return(1);
}


func IsAlchemContainer() { return(true); }
func AlchemProcessTime() { return(200); }


/* Kann in der Chemiefabrik hergestellt werden */
public func IsChemicalProduct() { return(1); }

