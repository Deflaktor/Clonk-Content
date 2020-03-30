Initialize:
  SetAction("Los");
  return(1);

Test:
  if(SetLocal(0,FindObject(MA3A,-100,-70,200,200))) SetAction("Speak1");
  if(SetLocal(0,FindObject(KR3A,-100,-70,200,200))) SetAction("Speak1");
  if(SetLocal(0,FindObject(WL3A,-100,-70,200,200))) SetAction("Speak1");
  return(1);

Text1:
  Message("%s: Man bräuchte hier eine Brücke um über den Vulkan zu kommen...",Local(0),GetName(Local(0)));
  return(1);

Fertig:
  SetVar(0,FindObject(_S10));
  SetLocal(1,Local(1,Var(0))|2,Var(0));
  RemoveObject();
  return(1);