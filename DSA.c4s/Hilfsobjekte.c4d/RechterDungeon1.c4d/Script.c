Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-50,-80,100,160,OCF_Prey())) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetPosition(0,0);

  CreateObject(FT3A,3485,425,-1);
  CreateObject(SC3A,3535,441,-1);

  CreateObject(KB3A,3140,565,-1);
  CreateObject(KB3A,3680,570,-1);
  CreateContents(OE3A,CreateObject(KB3A,4320,780,-1));
  CreateObject(KB3A,4520,700,-1);

  CreateObject(KA3A,3430,620,-1);
  CreateObject(KA3A,3820,440,-1);

  CreateContents(SP3A,CreateObject(KS3A,3540,620,-1));
  CreateObject(KS3A,3870,655,-1);
  CreateObject(KS3A,4390,560,-1);

  RemoveObject();
  return(1);