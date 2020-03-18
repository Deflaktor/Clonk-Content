#strict

Activate:
  SetVar(0,Random(3)+1);
  if(Var(0)==1)
    CreateConstruction(TRE1,0,15,-1,30);
  if(Var(0)==2)
    CreateConstruction(TRE2,0,15,-1,30);
  if(Var(0)==3)
    CreateConstruction(TRE3,0,15,-1,30);
  RemoveObject();
  Sound("FlourHit");
  Sound("Grab");
  return(1);

Hit:
  Sound("FlourHit");
  return(1);