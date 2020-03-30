Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-50,-100,100,200,OCF_Prey())) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetPosition(0,0);
  SetVar(0,CreateObject(TR3A,4125,1200,-1));
  CreateContents(R73A,Var(0));
  CreateContents(SK3A,Var(0));

  CreateObject(KB3A,4545,1170,-1);

  CreateObject(KA3A,4300,1280,-1);

  CreateObject(KS3A,4190,1190,-1);

  CreateObject(DF3A,4843,1246,-1);
  CreateObject(DF3A,4883,1246,-1);
  CreateObject(DF3A,4923,1246,-1);
  CreateObject(DF3A,4963,1246,-1);

  CreateObject(DF3A,4863,1246,-1);
  CreateObject(DF3A,4903,1246,-1);
  CreateObject(DF3A,4943,1246,-1);

  SetLocal(9,1,CreateObject(NG3A,4875,1306));
  SetLocal(9,1,CreateObject(NG3A,4935,1306));

  CreateConstruction(ELE2,4775,1172,-1,100,1);

  RemoveObject();
  return(1);