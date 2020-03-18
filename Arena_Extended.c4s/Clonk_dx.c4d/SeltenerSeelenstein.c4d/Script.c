#strict

Initialize:
  SetAction("Timer");
  return(1);

Hit:
  Sound("god");
  return(1);

NoShiftOwner:
  return(1);

Activate:
  SetVar(0,GetWealth(GetOwner(Par(0))));
  SetVar(0,Var(0));
  if(Var(0)>2000)
    SetVar(0,2000);
  SetWealth(GetOwner(Par(0)),GetWealth(GetOwner(Par(0)))+Var(0));
  Sound("Frag");
  SetVar(0,Var(0)/2);
  if(Var(0)>1000)
    SetVar(0,1000);
  SetVar(1,Var(0)/50);
  CastObjects(SPRK,Var(0)/5,10+Var(1));
  CastObjects(SPRK,Var(0)/5,20+Var(1));
  CastObjects(SPRK,Var(0)/5,30+Var(1));
  CastObjects(SPRK,Var(0)/5,40+Var(1));
  CastObjects(SPRK,Var(0)/5,50+Var(1));
  RemoveObject(this());
  return(1);

Destroy:
SetWealth(Par(0),GetWealth(Par(0))+Var(0));
return(0);

Delete:
  Sound("god");
  RemoveObject(this());
  return(1);

Check:
  return(1);
