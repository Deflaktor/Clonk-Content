Initialize:
  SetAction("Los");
  return(1);

Test:
  if(SetLocal(0,FindObject(MA3A,-100,-70,200,200))) SetAction("Speak1");
  if(SetLocal(0,FindObject(KR3A,-100,-70,200,200))) SetAction("Speak1");
  if(SetLocal(0,FindObject(WL3A,-100,-70,200,200))) SetAction("Speak1");
  return(1);

Text1:
  Message("%s: Da drüben scheint die Erde sehr locker zu sein...",Local(0),GetName(Local(0)));
  return(1);


Fertig:
  RemoveObject();
  return(1);