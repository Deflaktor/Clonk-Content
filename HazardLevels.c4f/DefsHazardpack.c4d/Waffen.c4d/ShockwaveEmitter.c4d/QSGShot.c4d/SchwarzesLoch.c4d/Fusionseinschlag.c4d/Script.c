#strict

Initialize:
  SetAction("Start");
  Sound("shockwave");
  SetComponent(HARD,1);
  SetLocal(0,40);
  return(1);  

Init:
  DoCon(Par(0)-100);
  return(1);

Kill:
  while(And(SetVar(0,FindObject(0,0,0,-1,-1,0,0,0,NoContainer(),Var(0))),LessThan(ObjectDistance(this(),Var(0)),40))) GetIt(Var(0));
  SetLocal(2,Sub(Local(2),1));
  if(Equal(Local(2),0)) SetAction("Die");
  return(1);
GetIt:
  if(And(Not(BitAnd(GetOCF(Par(0)),OCF_Living())),Not(FindObject(MR3V,0,0,0,0,0,"Hang",Par(0))))) return(0);
  if(Not(PathFree(GetX(),GetY(),GetX(Par(0)),GetY(Par(0))))) return(0);
  ObjectCall(Par(0),"Damage",Mul(GetComponent(HARD),Sub(Mul(-1,Div(Local(3),8))),Random(2)),GetOwner(),0,0,C4Id("A83V"));
  return(0);
Remove:
  while(LessThan(Var(2),361)) And(SetR(Var(2),CreateObject(_PUL,0,0,GetOwner(this()))),SetVar(2,Sum(Var(2),15)));
for (var i=0;i<GetCon()/100;i++)
{
  SetVar(2);
  while(LessThan(Var(2),361)) And(LaunchLightning(GetX(),GetY(),Sin(Var(2),15),20,Cos(Var(2),15),20),SetVar(2,Sum(Var(2),15)));
}
  CastObjects(SPRK,GetCon(),100);
  ObjectCall(CreateObject(EXPL),"Launch",6*GetCon()/10);
  return(RemoveObject());

