#strict

Launch:
  SetPosition(GetX(),GetY()+32);
  // ObjectCall(CreateObject(_FX3),"Launch",this(),Par(0));
  Explode(Par(0));
  return(1);

Remove:
  RemoveObject();
  return(1);