//Author:major}

#strict

ThrowRock:
  if (GetComDir() == COMD_Left()) ThrowLeft();
  if (GetComDir() == COMD_Right()) ThrowRight();
  return(1);

ThrowRight:
  SetXDir(38,SetLocal(0,CreateObject(RCK2,10,5)));
  CreateParticle("MSpark",GetX(Local())-GetX(),GetY(Local())-GetY(),38,-45, 500, RGBa(200,50,50,80));
  SetYDir(-45,Local());
  DoCon(-15,Local());
  return(1);

ThrowLeft:
  
 
  SetXDir(-38,SetLocal(0,CreateObject(RCK2,-10,5)));
  CreateParticle("MSpark",GetX(Local())-GetX(),GetY(Local())-GetY(),-38,-45, 500, RGBa(200,50,50,80));
  SetYDir(-45,Local());
  DoCon(-15,Local());
  return(1);

Activate:
  if (GetDir(Par(0))==DIR_Left()) SetComDir(COMD_Left());
  if (GetDir(Par(0))==DIR_Right()) SetComDir(COMD_Right());
  Sound("Magic1");
  ObjectSetAction(Par(),"Throw");
  SetAction("wait");
  return(1);


  