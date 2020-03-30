Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-100,-100,200,200,OCF_CrewMember())) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetPosition(0,0);
  CreateContents(R23A,CreateObject(TR3A,270,1070,-1));

  CreateObject(KB3A,20,1110,-1);
  CreateObject(KB3A,20,920,-1);
  CreateObject(KB3A,45,950,-1);
  CreateObject(KB3A,30,620,-1);
  CreateObject(KB3A,3,600,-1);
  CreateObject(KB3A,400,935,-1);

  CreateContents(SP3A,CreateObject(KA3A,390,1160,-1));
  CreateObject(KA3A,130,1160,-1);
  CreateObject(KS3A,60,960,-1);
  CreateObject(KA3A,278,1064,-1);
  CreateObject(KS3A,288,1064,-1);

  CreateObject(EFLN,990,1110,-1);
  CreateObject(EFLN,995,1110,-1);
  CreateObject(_RZS,982,1115,-1);

  CreateObject(_RW1,850,1080,-1);

  RemoveObject();
  return(1);