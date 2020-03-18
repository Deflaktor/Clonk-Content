#strict

local tanzen, actions;

Completion:
  SetAction("Tanzen");
  actions = 5;
  return(1);
  
Death:
  CastObjects(SPRK,20,20);
  CastObjects(SPRK,20,40);
  CastObjects(SPRK,20,10);
  RemoveObject(this());
  return(1);
 
Activity:
  DoEnergy(100);
  return(1);
  
Incineration:
  Extinguish();
  return(1);
  
Getanzt:
  tanzen++;
  if(actions<=0&&tanzen>5)
    return(Kill());
  if(tanzen>5) {
    Sound("Devil");
    SetAction("Fire");
  }
  return(1);
  
Damaged:
  return(1);
  
Gefeuert:
  if(actions==5&&!Random(2))
    CastAllies();
  else if(actions==5)
    IncinerateEveryone();
  else
    DamageEveryone();
  tanzen=2;
  SetAction("Tanzen");
  return(1);

CastAllies:
  actions=0;
  for(var i = 0; i<20; i++) {
    SetVar(0,CreateObject(RandomEnemy(),0,-20));
    ObjectSetAction(Var(0),"Tumble");
    Fling(Var(0),Sub(Random(100),50),Sub(Random(100),100));
	SetOwner(GetOwner(),Var(0));
  }
  return(1);
  
NoShiftOwner:
  return(1);
  
DamageEveryone:
  actions--;
  while(SetVar(0,FindObject(0,0,0,0,0,OCF_Living(),0,0,0,Var(0)))) {
    if(TargetOk(Var(0)))
	  CreateObject(PRNT,AbsX(GetX(Var(0))),AbsY(GetY(Var(0))),GetOwner())->Explode(70);
  }
  return(1);
  
IncinerateEveryone:
  actions--;
  while(SetVar(0,FindObject(0,0,0,0,0,OCF_Living(),0,0,0,Var(0)))) {
    if(TargetOk(Var(0)))
	  Incinerate(Var(0));
  }
  return(1);

TargetOk:
  if (GetOwner()==GetOwner(Par(0)))
    return(0);
  if (!GetAlive(Par(0)))
    return(0);
  return(1);
  
RandomEnemy:
  var i=Random(10);
  if(i==0) return(KI58);
  if(i==1) return(DIL1);
  if(i==2) return(KIK1);
  if(i==3) return(GIK1);
  if(i==4) return(KB3A);
  if(i==5) return(KIL1);
  if(i==6) return(WIG1);
  if(i==7) return(MF5B);
  if(i==8) return(MONS);
  return(C158);
  
