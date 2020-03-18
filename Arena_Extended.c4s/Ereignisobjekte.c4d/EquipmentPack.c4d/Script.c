#strict

Initialize:
  return(1);


Entrance:
  ObjectSetAction(CreateContents(BALL,Par(0)),"Exist");
  CreateContents(KREI,Par(0));
  CreateContents(_MF6,Par(0));
  if(Local(4,Par(0))==1)
    return(RemoveObject(this()));
  SetLocal(4,1,Par(0));
  // SetPhysical("Energy",GetPhysical("Energy",0,Par(0))+100000,2,Par(0));
  if(Local(3,Par(0))==0)
  {
    SetPhysical("Walk",GetPhysical("Walk",0,Contained())+20000,2,Contained());
    SetPhysical("Jump",GetPhysical("Jump",0,Contained())+4000,2,Contained());
  }
  SetLocal(2,10,Par(0));
  RemoveObject(this());
  return(0);

Effects:
  CastParticles("PxSpark", 2, 20, AbsX(GetX()-5+Random(10)), AbsY(GetY()-5+Random(15)), 5*10, 10*10, RGBa(0, 100, 100, 140), RGBa(0, 200, 200, 140));
  return(1);