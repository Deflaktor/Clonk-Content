/*--- Kohle ---*/

#strict

protected func Initialize()
{
  if (Stuck()) SetPosition(GetX(), GetY() - 2);
  return(1);
}

protected func Hit()
{
  Sound("RockHit*");
  return(1);
}

/* Kann in der Chemiefabrik hergestellt werden */
public func IsChemicalProduct() { return(1); }

func IsAlchemContainer() { return(true); }
func AlchemProcessTime() { return(100); }

public GetResearchBase: return(ALC_);