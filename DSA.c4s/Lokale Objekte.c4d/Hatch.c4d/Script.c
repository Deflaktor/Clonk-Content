Initialize:
  SetSolidMask(3,16,18,4,3,16);
  return(1);

CheckArea:
  // Kiste unter der Klappe suchen
  PushUp(FindObject(TR3A, -10,0,24,10));
  PushUp(FindObject(_I10, -10,0,24,10));
  return(1);

PushUp:
  if(!Par(0))
    return(0);
  SetPosition(GetX(Par(0)),GetY(Par(0))-2, Par(0));
  return(1);