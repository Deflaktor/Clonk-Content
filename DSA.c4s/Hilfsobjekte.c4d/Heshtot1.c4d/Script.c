Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-100,-100,200,200,OCF_CrewMember())) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetPosition(0,0);
  CreateObject(FT3A,3685,1250,-1);
  CreateObject(SC3A,3735,1266,-1);

  Enter(CreateObject(TR3A,3850,1230,-1),FindObject(MS3A,2200,1180,80,80));

  CreateObject(KB3A,2335,920,-1);
  CreateObject(KB3A,3645,1155,-1);
  CreateObject(KB3A,3875,1200,-1);

  CreateContents(MT3A,CreateObject(TR3A,2360,1160,-1));
  CreateContents(R63A,CreateObject(TR3A,2070,1160,-1));
  CreateObject(TR3A,3040,1070,-1);

  CreateObject(KA3A,2220,970,-1);
  CreateObject(KA3A,2950,1250,-1);
  CreateObject(KA3A,3830,1260,-1);
  CreateObject(KS3A,3040,1070,-1);
  CreateObject(KS3A,3600,1230,-1);
  CreateObject(KS3A,3670,1160,-1);
  RemoveObject();
  return(1);