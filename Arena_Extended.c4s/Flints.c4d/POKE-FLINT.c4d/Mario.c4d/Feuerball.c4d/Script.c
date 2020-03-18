Initialize:
  SetAction("Start");
  return(1);

Init:
  SetLocal(0,GetXDir());
  SetLocal(1,Local(0)*20);
  return(1);

Hit:
  SetYDir(-30);
  return(1);

Checkit:
  SetXDir(Local(0));
  SetRDir(Local(1));
  if(GetX()==Local(3)&&GetY()==Local(4)) {
    SetPosition(GetX(),GetY()-1);
    SetLocal(5,Local(5)+1);
  }
  if(Local(5)>20)
    RemoveObject();
  if(GetX()>LandscapeWidth()-2||GetX()<2)
    RemoveObject();
  while(SetVar(2,FindObject(0,-8,-8,16,16,OCF_Alive(),0,0,NoContainer(),Var(2))))
    if(GetOwner(Var(2))!=GetOwner()) {
      CastObjects(LEI8,5,10);
      DoEnergy(-10,Var(2));
      RemoveObject();
    }
  SetLocal(3,GetX());
  SetLocal(4,GetY());
  return(1);