/* Abflussrohr */
#strict

Imu:
  while(SetVar(0,FindObject(0, -24,-8,48,64,0,0,0,NoContainer(),Var(0)))) Repel(Var(0));
  var c = 20+Random(41);
  CreateParticle("PxSpark",0,-7+Random(14), -10+Random(20), 50+Random(50), c, RGBa(125, 125, 125, 150));
  CreateParticle("PxSpark",0,-7+Random(14), -10+Random(20), 50+Random(50), c, RGBa(125, 125, 125, 150));
  CreateParticle("PxSpark",0,-7+Random(14), -10+Random(20), 100+Random(50), c, RGBa(125, 125, 125, 150));
  return (1);

Still:
  SetAction ("Idle");
  return (1);

NuuNuu:
  SetAction ("Drain");
  return (1);
  
Check:
  if (GameCall("MainEnergySupply")&&FindObject(_BMA))
    if (ActIdle())
      NuuNuu();
  if (!GameCall("MainEnergySupply")||!FindObject(_BMA))
    if (!ActIdle())
      Still();
  return(1);
  
Repel:
  if( GetOwner(Par(0))==GetOwner(Contained(GetActionTarget()))&&Contained(GetActionTarget()) )
    return(1);
  if(Par(0)==GetActionTarget())
    return(1);
  if(GetMass(Par(0))>=200)
    return(1);
  if(!(GetCategory(Par(0)) & C4D_Object()||GetCategory(Par(0)) & C4D_Living()))
    return(1);
  if(GetID(Par(0))==_HGG||GetID(Par(0))==_HG2)
    return(1);
  SetVar(1,Sub(GetX(),GetX(Par(0))));
  SetVar(2,Sub(GetY(),GetY(Par(0))));
  if(GetID(Par(0))!=ST5B||!Random(5))
    DoEnergy(-1,Par(0));
  Fling(Par(0),0,-10);
  SetSpeed(-Var(1),-Var(2)+30,Par(0));
  if(SEqual(GetAction(Par(0)),"Travel")) {
    SetLocal(0,-Var(1)*2,Par(0));
    SetLocal(1,-Var(2)*2,Par(0));
    if (Local(0,Par(0))<0) SetDir(DIR_Left(),Par(0));
    else SetDir(DIR_Right(),Par(0));
  }
  if(ObjectCall(Par(0),"IsProjectile"))
    SetOwner(GetOwner(Contained(GetActionTarget())),Par(0));
  return(1);