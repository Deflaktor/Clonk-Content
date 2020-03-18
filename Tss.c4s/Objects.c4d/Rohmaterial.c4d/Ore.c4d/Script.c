/*--- Eisenerz ---*/

#strict

func Hit () {
  Sound("RockHit*");
}

func IsAlchemContainer() { return(true); }
func AlchemProcessTime() { return(200); }

/* Kann in der Chemiefabrik hergestellt werden */
public func IsChemicalProduct() { return(1); }

public GetResearchBase: return(ALC_);