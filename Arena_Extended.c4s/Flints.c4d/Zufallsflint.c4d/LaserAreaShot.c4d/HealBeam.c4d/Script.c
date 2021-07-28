/*--- Laserstrahl ---*/

Initialize:
  // Local 0 und 1 sind die Lininenfarben (grün)
  SetLocal(0,47);
  SetLocal(1,47);
  // Die ersten beiden Vertices auf aktuelle Position legen
  SetVertex(0,0,GetX()); 
  SetVertex(0,1,GetY());
  SetVertex(1,0,GetX()); 
  SetVertex(1,1,GetY());
  return(1);

Connect:
  SetAction("Connect",Par(0),Par(1));
  return(1);
  
Launch:
  SetAction("Brutzel",Par(0),Par(1));
  SetLocal(4, Par(2));
  //Sound("LaserShot1");
  return(1);  
  
DamageTarget:
  SetLocal(0,Local(1)-1+Random(2));
  SetLocal(3,Local(3)+1);

  DoEnergy(-1,GetActionTarget(1));
  DoEnergy(1,GetActionTarget(1,Local(4)));

  CastObjects(SPK2,5,10,Sub(GetVertex(1,0),GetX()),Sub(GetVertex(1,1),GetY(),15));
  if (Local(3)>2)
    RemoveObject();
  return(1);