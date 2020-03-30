Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-10,-10,200,200,OCF_Prey())) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetPosition(0,0);
  CreateContents(R33A,CreateObject(TR3A,4220,900,-1));

  CreateObject(KB3A,4300,1010,-1);
  CreateObject(KB3A,4180,1000,-1);

  CreateObject(KA3A,4550,960,-1);

  CreateObject(KS3A,4120,980,-1);

  CreateConstruction(ELE2,3995,991,-1,100,1);

  RemoveObject();
  return(1);