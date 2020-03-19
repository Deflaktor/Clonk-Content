#strict

Start:
  SetAction("Drehen");
  if (Equal(Par(0),DIR_Left())) SetVar(0,2);
  if (Equal(Par(0),DIR_Right())) SetVar(0,-2);
  SetDir(Par(0));
  SetXDir(Mul(Sum(Random(10),5),Var(0)));
  SetYDir(Sum(Random(10),-20));
  return(1);

Test:
  SetLocal(0,Sum(Local(0),1));
  if (GreaterThan(Local(0),10)) RemoveObject();
  return(1);

Hit:
  if(Random(3))
  return(RemoveObject());
  SetAction("Stop");
  Sound("Huelse");
  return(1);