Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-100,-100,200,200,OCF_CrewMember())) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetPosition(0,0);
  CreateContents(EX3A,CreateObject(TR3A,1040,1250,-1));

  CreateObject(KB3A,1645,1170,-1);
  CreateObject(KB3A,1070,1190,-1);
  CreateObject(KB3A,1370,1170,-1);
  CreateObject(KB3A,1350,1150,-1);

  CreateContents(SP3A,CreateObject(KS3A,1550,1210,-1));
  CreateContents(SP3A,CreateObject(KA3A,1380,1110,-1));
  CreateObject(KS3A,1070,1190,-1);
  RemoveObject();
  return(1);