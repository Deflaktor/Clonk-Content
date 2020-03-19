/*--- Laserstrahl ---*/

Initialize:
  // Local 0 und 1 sind die Lininenfarben

  // Die ersten beiden Vertices auf aktuelle Position legen
  SetVertex(0,0,GetX()); SetVertex(0,1,GetY());
  SetVertex(1,0,GetX()); SetVertex(1,1,GetY());
  return(1);

Connect:
  SetAction("Connect",Par(0),Par(1));
  return(1);
  
Launch:
  if(Par(2)) {
    // rot
    SetLocal(0,47);
    SetLocal(1,47);
	SetAction("Brutzel2",Par(0),Par(1));
  } else {
    // grün
    SetLocal(0,52);
    SetLocal(1,52);
	SetAction("Brutzel",Par(0),Par(1));
  }
  
  //Sound("LaserShot1");
  return(1);  
  
DamageTarget:
  SetLocal(0,Local(1)-2+Random(4));
  SetLocal(3,Local(3)+1);
  //DoEnergy(-1,GetActionTarget(1));
  if(GetAlive(GetActionTarget(1)))
    DoEnergy(Dmg(0)/4,Contained(GetActionTarget(0)));
  Punch(GetActionTarget(1),Dmg(0)/4); 
  DoDamage(Dmg(0)/4,GetActionTarget(1));

  CastObjects(SPK2,5,10,Sub(GetVertex(1,0),GetX()),Sub(GetVertex(1,1),GetY(),15));
  if (Local(3)>4)
    RemoveObject();
  return(1);
  
DoubleDamageTarget:
  SetLocal(0,Sum(43,Random(5)));
  SetLocal(3,Local(3)+1);
  //DoEnergy(-1,GetActionTarget(1));
  if(GetAlive(GetActionTarget(1)))
    DoEnergy(-Dmg(0)/4,Contained(GetActionTarget(0)));
  Punch(GetActionTarget(1),Dmg(1)/4);
  DoDamage(Dmg(1)/4,GetActionTarget(1));

  CastObjects(SPK2,5,10,Sub(GetVertex(1,0),GetX()),Sub(GetVertex(1,1),GetY(),15));
  if (Local(3)>4)
    RemoveObject();
  return(1);
  
Dmg:
  if(Par(0)) 
    return(3*4);
  return(1*4);