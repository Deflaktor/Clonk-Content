#strict

Launch:
  SetClrModulation(RGBa(255,255,255,10));
  DoCon(Sub(Div(Mul(Par(0),100),20),100));
  SetLocal(0,Par(0));
  SetVar(0,Mul(Div(Sub(64,Div(Mul(64,GetCon()),100)),2),-1));
  SetPosition(GetX(),Sum(GetY(),Var(0)));
//  SetVar(1,FindObject(0,Mul(-1,Sum(Div(Local(0),2),5)),Mul(-1,Sum(Div(Local(0),2),5)),Sum(Local(0),10),Sum(Local(0),10),OCF_Living()));
//  SetComponent(EXPL,Sum(1,GetOwner()),Var(1));
//  while(SetVar(1,FindObject(0,Mul(-1,Sum(Div(Local(0),2),5)),Mul(-1,Sum(Div(Local(0),2),5)),Sum(Local(0),10),Sum(Local(0),10),OCF_Living(),0,0,0,Var(1)))) SetComponent(EXPL,Sum(1,GetOwner()),Var(1));
//  BlastObjects(GetX(),GetY(),Div(Local(0),1));
  DigFree(GetX(),GetY(),Div(Local(0),1));
if(Local(0)<20)
  Sound("Blast1");
  Sound("Blast1");
  Sound("Blast1");
if(Local(0)>20)
if(Local(0)<60)
  Sound("Blast2");
  Sound("Blast2");
  Sound("Blast2");
if(Local(0)>60)
  Sound("Blast3");
  Sound("Blast3");
  Sound("Blast3");
  return(1);
Initialize:
  SetAction("Blast");
  SetLocal(0,64);
  return(1);  
Remove:
  RemoveObject();
  return(1);