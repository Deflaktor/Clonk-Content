Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-100,-50,200,100,OCF_CrewMember())) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetPosition(0,0);
  CreateContents(_ZKI,CreateObject(TR3A,2555,1240,-1));
  CreateContents(R53A,CreateObject(TR3A,2590,1240,-1));

  CreateObject(KB3A,2370,1370,-1);

  CreateObject(KA3A,3410,1350,-1);
  CreateObject(KA3A,3050,1364,-1);

  CreateObject(KS3A,2720,1330,-1);

  RemoveObject();
  return(1);