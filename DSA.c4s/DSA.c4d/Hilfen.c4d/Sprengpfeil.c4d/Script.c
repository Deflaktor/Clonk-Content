Initialize:
  //SetLocal(1,Contained());
  SetAction("Shot");
  return(1);

Hit:
  SetLocal(8,GetX(),Local(1));
  SetLocal(9,GetY(),Local(1));
  Explode(Sum(10,Random(5)));
  return(1);

InFlight:
  while (SetVar(0,FindObject(0,+1,+1,0,0,0,0,0,NoContainer(),Var(0))))
    if (ObjectCall(Var(0),"IsArrowTarget"))
      return(HitTarget(Var(0)));
  return(1);

HitTarget:
  Explode(Sum(10,Random(5)));
  return(1);


