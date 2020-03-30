Hit:
  if(SEqual(GetAction(),"Active"))
    return(1);
  CastObjects(HF3A, 40, 60 );
  SetAction("Active");
  Sound("PengKlirr");
  return(1);

Brenn:
  CastObjects(HF3A, 10, 60 );
  return(1);

Ende:
  RemoveObject();
  return(1);