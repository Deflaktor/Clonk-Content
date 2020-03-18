#strict

Shiver:
  SetXDir(Random(21)-10);
  if (!InLiquid()) Remove();
  return(1);

Initialize:
  if(!GBackLiquid()) return(RemoveObject());
  SetAction("Bubble");
  SetComDir(COMD_Up());
  SetXDir(Random(21)-10);
//  Shiver();
  return(1);

Remove:
  RemoveObject();
  return(1);
