/*-- Kochen --*/

#strict
#appendto DBRD
#appendto DFSH
#appendto SNKE

public func Bake() {
  return(this()->Cook());
}

public func IsDough() {
  if (GetAction() S= "Decay") return(0);
  return(1);
}
