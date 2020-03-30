Initialize:
  SetAction("Los");
  return(1);

Test:
  if(FindObject(0,-100,-100,200,200,OCF_Prey())) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetPosition(0,0);
  CreateContents(_ZKH,CreateObject(TR3A,5150,1050,-1));

  CreateConstruction(ELE2,5265,1052,-1,100,1);
  CreateConstruction(ELE2,5055,1152,-1,100,1);
  CreateConstruction(ELE2,5935,1172,-1,100,1);

  CreateConstruction(_MES,5870,1060,-1,100,0);

  SetLocal(9,1,CreateObject(NG3A,5140,1250));
  SetLocal(9,1,CreateObject(NG3A,5155,1250));
  SetLocal(9,1,CreateObject(NG3A,5172,1250));

  CreateObject(_RZG,5430,1050);

  RemoveObject();
  return(1);