Initialize:
  SetAction("Los");
  return(1);

Test:
  if(SetLocal(1,FindObject(0,-50,-50,100,100,OCF_Prey()))) SetAction("AbdiePost");
  return(1);

Erstellen:

  while(SetVar(0,FindObject(FT33,-200,-100,400,200, 0, 0,0, NoContainer(), Var(0)))) 
    SetLocal(1,1,Var(0));

  return(1);