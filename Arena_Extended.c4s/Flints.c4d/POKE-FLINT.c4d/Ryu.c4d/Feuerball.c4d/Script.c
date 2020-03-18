Initialize:
  SetAction("Start");
  return(1);

Init:
  SetLocal(0,GetXDir());
  if(GetXDir()>0)
    SetDir(DIR_Right());
  else
    SetDir(DIR_Left());
  return(1);

Hit:
  RemoveObject();
  return(1);

Checkit:
  SetYDir(0);
  SetXDir(Local(0));
  while(SetVar(2,FindObject(0,-8,-8,16,16,OCF_Alive(),0,0,NoContainer(),Var(2))))
    if(GetOwner(Var(2))!=GetOwner()) {
      CastObjects(LEI8,5,10);
      DoEnergy(-17,Var(2));
      RemoveObject();
    }
  return(1);