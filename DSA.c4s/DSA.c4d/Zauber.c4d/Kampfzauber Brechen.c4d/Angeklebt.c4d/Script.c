sterb:
  RemoveObject();
  return(1);

wechdamit:
  if(SetVar(0,FindObject(0,-50,-50,100,100,OCF_OnFire()))) Extinguish(Var(0));
  if(SetVar(0,FindObject(0,-50,-50,100,100,OCF_OnFire()))) Extinguish(Var(0));
  if(SetVar(0,FindObject(0,-50,-50,100,100,OCF_OnFire()))) Extinguish(Var(0));
  if(SetVar(0,FindObject(0,-50,-50,100,100,OCF_OnFire()))) Extinguish(Var(0));
  if(SetVar(0,FindObject(0,-50,-50,100,100,OCF_OnFire()))) Extinguish(Var(0));
  if(SetVar(0,FindObject(0,-50,-50,100,100,OCF_OnFire()))) Extinguish(Var(0));
  if(SetVar(0,FindObject(0,-50,-50,100,100,OCF_OnFire()))) Extinguish(Var(0));
  if(SetVar(0,FindObject(0,-50,-50,100,100,OCF_OnFire()))) Extinguish(Var(0));
  while(SetVar(1,FindObject(BF3A,-50,-50,100,100,0,"Daswars"))) RemoveObject(Var(1));
  while(SetVar(2,FindObject(GV3A,-50,-50,100,100,0,"Daswars"))) RemoveObject(Var(2));
  return(1);