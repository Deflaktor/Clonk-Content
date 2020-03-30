Initialize:
  SetAction("Los");
  return(1);

Test:
  if(SetLocal(1,FindObject(0,-50,-50,100,100,OCF_Prey()))) SetAction("AbdiePost");
  return(1);

Erstellen:

  while(SetVar(0,FindObject(_GS1,-200,-100,400,200, 0, 0,0, NoContainer(), Var(0)))) 
    SetLocal(1,1,Var(0));

  while(SetVar(0,FindObject(_GS7,-200,-100,400,200, 0, 0,0, NoContainer(), Var(0)))) 
    SetLocal(1,1,Var(0));

  while(SetVar(0,FindObject(_GS8,-200,-100,400,200, 0, 0,0, NoContainer(), Var(0)))) 
    SetLocal(1,1,Var(0));

  return(1);