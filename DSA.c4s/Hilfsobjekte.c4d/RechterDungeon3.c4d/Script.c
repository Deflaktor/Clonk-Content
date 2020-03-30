Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-50,-50,100,100,OCF_Prey())) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetPosition(0,0);
  CreateContents(_ZKR,CreateObject(TR3A,4720,630,-1));
  CreateContents(R43A,CreateObject(TR3A,4940,640,-1));

  CreateObject(KB3A,4895,890,-1);

  CreateObject(KA3A,4940,640,-1);

  CreateObject(KS3A,4940,640,-1);
  CreateObject(KS3A,4970,920,-1);

  RemoveObject();
  return(1);