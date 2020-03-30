/*-- Toter Fisch --*/

#strict

private func Decaying() 
{ 
  DoCon(-4); 
}

public func Cook()
{
  // Verwesende Fische können nicht mehr gekocht werden
  if (GetAction() S= "Decay") return(0);
  // Kochen
  ChangeDef(CFSH);
  return(1);
}

/* Aufwertungszauberkombo: Mit Fisch wird der Clonk zum Aquaclonk */
public func GetRevaluationCombo(object pClonk) {
  if (GetAction() S= "Decay") return(0);
  return(ACLK);
}
