#strict

Entrance:
  Contained()->Local(3)++;
  Sound("Magic");
  CastObjects(_SK2,20,20);
  CastObjects(_SK2,100,200);
  RemoveObject(this());
  return(1);
  
NoCollectLimit:
  return(1);