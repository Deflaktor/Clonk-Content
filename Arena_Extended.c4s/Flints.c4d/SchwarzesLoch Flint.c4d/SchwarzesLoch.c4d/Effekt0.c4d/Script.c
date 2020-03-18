#strict

Initialize:
  //DoCon(100);
  return(SetAction("Fly"));

Start:
  SetXDir(Cos(GetR(),100));
  SetYDir(Sin(GetR(),100));
  return(1);

Check:
  if(GBackSolid()) RemoveObject();
  return(1);

Timer:
  BlastObjects(GetX(),GetY(),5);
  if(Equal(Local(1),10)) RemoveObject();
  SetLocal(1,Sum(Local(1),1));
  return();

Completion:
  SetLocal(0,Sum(35000,Random(10000)));
  return(SetAction("FlyArround"));
Hit:
  Sound("Plumps");
  return(SetAction("CauseDamage"));
Dangerous:
  while(SetVar(0,FindObject(0,-60,-60,120,120,OCF_Prey(),0,0,NoContainer(),Var(0)))) Harm(Var(0));
  if(GreaterThan(GetActTime(this()),Local(0))) return(RemoveObject());
  return(1);
Harm:
  DoEnergy(-20,Par(0));
  return(1);