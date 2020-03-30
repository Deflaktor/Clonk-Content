Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-100,-100,200,200,OCF_CrewMember())) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetPosition(0,0);
  SetVar(0,CreateObject(TR3A,960,80,-1));
  ObjectCall(Var(0),"Bonus",OE3A,3);
  ObjectCall(Var(0),"Bonus",P63A,5);
  Enter(Var(0),FindObject(MS3A,800,50,200,200));

  CreateObject(_GEF,1400,260,-1);
  
  CreateObject(FT3A,1465,260,-1);
  CreateObject(SC3A,1515,276,-1);

  CreateObject(KB3A,1600,300,-1);
  CreateObject(KB3A,2010,190,-1);
  CreateObject(KB3A,2210,80,-1);

  CreateObject(KS3A,2410,140,-1);
  CreateContents(OE3A,CreateObject(KA3A,2220,140,-1));
  CreateObject(KA3A,2750,40,-1);
  CreateObject(KA3A,2640,170,-1);
  CreateObject(KA3A,1890,320,-1);
  CreateObject(KA3A,1710,320,-1);
  CreateObject(KS3A,1870,180,-1);
  RemoveObject();
  return(1);