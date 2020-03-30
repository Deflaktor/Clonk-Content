Completion:
  SetAction("Check");
  SetComDir(COMD_Stop());
  return(1);

CheckEnergy:
  SetCon(Max(GameCall("GetGlobalEnergy"),1));
  return(1);

SetCon:
  DoCon(Sub(Par(0),GetCon()));
  return(1);
