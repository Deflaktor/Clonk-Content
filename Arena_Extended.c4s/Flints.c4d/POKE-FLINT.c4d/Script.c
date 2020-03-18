#strict
#include PRNT

/*-- Tera-Flint --*/

/* Aufschlag */

protected Hit:
  if(!Random(50)) {
    SetOwner(GetOwner(),CreateObject(DI7B,0,-20));
	return(Effekt());
  }
  var threattype = Random(5);
  if(threattype == 0)
    SetOwner(GetOwner(),CreateObject(KI60));
  if(threattype == 1)
    SetOwner(GetOwner(),CreateObject(PIKA));
  if(threattype == 2)
    SetOwner(GetOwner(),CreateObject(MRIO));
  if(threattype == 3)
    SetOwner(GetOwner(),CreateObject(_RYU));
  if(threattype == 4)
    SetOwner(GetOwner(),CreateObject(ROK1));
  Effekt();
  return(1);

Effekt:
  CastObjects(SPRK,20,20);
  CastObjects(SPRK,20,40);
  CastObjects(SPRK,20,10);
  Sound("Pokeball");
  RemoveObject();
  return(1);
  
Departure:
  SetOwner(GetOwner(Par(0)),this());
  return(1);



