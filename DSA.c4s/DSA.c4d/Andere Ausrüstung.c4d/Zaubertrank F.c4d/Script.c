Hit:
  Sound("bottle");
  return(1);
Activate:
  if(GetID(Par(0))==KR3A||GetID(Par(0))==KRRA)
    return(0);

  while(DoMagicEnergy(1,Contained(this()))) And();
  //Sound("Magic1");
  CreateObject(GL3A);
  RemoveObject(this());
  return(1);