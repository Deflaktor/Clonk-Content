#strict

protected Initialize:
  SetPosition();
  return(1);

DoRocks:
  if(Not(Random(150)))
    And(
        SetVar(0,CreateObject(GIK1,GetXPos(),0,-1)),
        SetXDir(Sub(25,Random(51)),Var(0)),
        SetYDir(Sum(20,Random(16)),Var(0))
       );
  return(1);
  
GetXPos:
  Var(1) = Random(LandscapeWidth());
  if(Var(1)=FindObject(MNTK)) {
    if(Var(1)=Var(1)->GetCurrentGod()) {
      Var(1) = GetX(Var(1))-40+Random(80);
    }
  }
  return(Var(1));