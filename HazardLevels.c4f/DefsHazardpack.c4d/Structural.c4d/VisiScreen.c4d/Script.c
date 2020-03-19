#strict

Completion:
  SetAction("Locate");
  return(1);
Locate:
  RemovePreviousDots();
  CreateDots();
  return(1);
Damage:
  if (SEqual(GetAction(),"Broken")) return(0);
  SetAction("Broken");
  CastObjects(SHRD,20,10,32,15);
  Sound("GlassBreak");
  return(1);
RemovePreviousDots:
  if(Not(SetVar(0,FindObject(_DOT,-10,-10,90,50)))) return(1);
  RemoveObject(Var(0));
  return(RemovePreviousDots());

CreateDots:

  // For Var(0) = 0 To 11
  while(Var(0)=FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,0,Var(0)))
    CreateObject(_DOT,Div(Mul(GetX(Var(0)),64),LandscapeWidth()),Div(Mul(GetY(Var(0)),34),LandscapeHeight()),-1);
  return(1);

Check:
  if (GameCall("MainEnergySupply", this()))
  if (GetAction()S="Aus")
  SetAction("Locate");
  if (Not(GameCall("MainEnergySupply", this())))
  if (GetAction()S="Locate")
  Aus();
  return(1);

Aus:
  RemovePreviousDots();
  SetAction("Aus");
  return(1);