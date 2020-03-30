/*-- Sägemehl --*/

protected Initialize:
  SetAction("Dust");
  SetPhase(Random(4));
  return(1);

protected Timer:
  if (Random(10)) RemoveObject();
  return(1);