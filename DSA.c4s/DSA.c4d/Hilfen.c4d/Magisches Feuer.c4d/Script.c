Completion:
  Incinerate();
  SetAction("Burn");
  SetComDir(COMD_Down());
  return(1);

WasnSchwein:
  Extinguish();
  SetAction("Machaus");
  return(1);

test:
  if(Random(3)) if(GreaterThan(GetActTime(),120)) Call("WasnSchwein");
  return(1);
  
loesch:
  Extinguish(FindObject(0,-600,-50,1200,50,OCF_OnFire()));
  if(Random(3)) if(GreaterThan(GetActTime(),80)) Call("fertig");
  return(1);

fertig:
  RemoveObject();
  AssignRemoval();
  return(1);

