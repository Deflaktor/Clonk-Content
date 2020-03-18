#strict
#appendto TREE

public func Reproduction()
{
  // Ist noch Platz für einen Baum?
  var iSize = ReproductionAreaSize();
  var iOffset = iSize / -2;
  if (ObjectCount(0, iOffset, -50, iSize, 100, OCF_Chop())<MaxTreeCount())
    // OK, hin damit
    return(PlaceVegetation(GetID(this()), iOffset, -50, iSize, 100, 10) );
  // Kein Platz ;'(
  return(0);
}