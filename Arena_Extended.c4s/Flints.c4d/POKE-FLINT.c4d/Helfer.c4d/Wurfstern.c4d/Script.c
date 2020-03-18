Initialize:
  SetAction("Start");
  return(1);

Init:
  SetLocal(0,GetXDir());
  SetLocal(1,GetYDir());
  return(1);

Hit:
  RemoveObject();
  return(1);

Checkit:
  SetXDir(Local(0));
  SetYDir(Local(1));
  while(SetVar(2,FindObject(0,-8,-8,16,16,OCF_Alive(),0,0,NoContainer(),Var(2))))
    if(GetOwner(Var(2))!=GetOwner()) {
      CastObjects(LEI8,2,10);
      DoEnergy(-5,Var(2));
      Hit();
    }
  return(1);