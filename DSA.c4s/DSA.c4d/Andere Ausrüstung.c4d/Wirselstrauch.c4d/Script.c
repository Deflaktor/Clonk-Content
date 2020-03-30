Initialize:
  return(1);

ControlUp:
  Enter(Par(0),this());
  ChangeDef(WK3A);
  return(1);

Machmehrdavon:
  if (Not(Random(5000)))  PlaceVegetation(GetID(this()),-400,-400,800,800,10);
  return(1);