/* Kraftfeldwand */
private func GetSegmentID() { return(FCWS); }

protected func Initialize()
{
  
    var pNext = CreateObject(GetSegmentID(), 0, GetDefCoreVal("Offset", "DefCore", GetID(), 1) + i*GetDefCoreVal("Height", "DefCore", GetSegmentID()), -1);
  
}