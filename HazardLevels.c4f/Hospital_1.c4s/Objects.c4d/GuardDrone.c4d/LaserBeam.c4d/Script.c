/*--- Laser ---*/

Initialize:
  // Local 0 und 1 sind die Lininenfarben
  SetLocal(0,47); 
  SetLocal(1,47);  
  // Die ersten beiden Vertices auf aktuelle Position legen
  SetVertex(0,0,GetX()); SetVertex(0,1,GetY());
  SetVertex(1,0,GetX()); SetVertex(1,1,GetY());
  return(1);

Connect:
  SetAction("Connect",Par(0),Par(1));
  return(1);
  
Launch:
  SetAction("Brutzel",Par(0),Par(1));
  //Sound("LaserShot1");
  return(1);  
  
DamageTarget:
  SetLocal(0,Sum(43,Random(5)));
  Punch(GetActionTarget(1),1);
  CastObjects(SPK2,5,10,Sub(GetVertex(1,0),GetX()),Sub(GetVertex(1,1),GetY(),15));
  if (Not(Random(3))) RemoveObject();
  return(1);