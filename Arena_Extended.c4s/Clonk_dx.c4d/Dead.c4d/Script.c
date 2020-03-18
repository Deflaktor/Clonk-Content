#strict

protected Initialize:
  SetVar(0,Sub(Random(80),40));
  SetXDir(Var(0));
  SetYDir(-90);
  SetRDir(60);
  return(1);

MakeSmaller:
  DoCon(-1);
  return(1);