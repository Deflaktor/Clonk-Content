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
  SetVar(0,-1);
  while ( LessThan( SetVar(0,Sum(Var(0),+1)), 12 ) )
    if ( SetVar(1,GetCrew(Var(0))) )
      CreateObject(_DOT,Div(Mul(GetX(Var(1)),64),LandscapeWidth()),Div(Mul(GetY(Var(1)),34),LandscapeHeight()),-1);
  return(1);

Check:
  if (GameCall("MainEnergySupply"))
  if (GetAction()S="Aus")
  SetAction("Locate");
  if (Not(GameCall("MainEnergySupply")))
  if (GetAction()S="Locate")
  Aus();
  return(1);

Aus:
  RemovePreviousDots();
  SetAction("Aus");
  return(1);