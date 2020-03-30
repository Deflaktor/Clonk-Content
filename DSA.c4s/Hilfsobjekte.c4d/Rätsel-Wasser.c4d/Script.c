Initialize:
  SetAction("Los");
  return(1);

Test:
  if(SetLocal(0,FindObject(MA3A,-100,-100,200,200)))
    if(SetLocal(1,FindObject(KR3A,-150,-150,300,300)))
      if(SetLocal(2,FindObject(WL3A,-200,-200,400,400)))
      SetAction("Speak1");
  return(1);

Text1:
  Message("%s: Hier tropft es ja von der Decke, wie eklig!",Local(0),GetName(Local(0)));
  return(1);

Text2:
  Message("%s: Immer diese weichlichen Magier.",Local(1),GetName(Local(1)));
  return(1);

Text3:
  Message("%s: Du hast warscheinlich nur nicht kapiert, dass das Wasser ist!",Local(0),GetName(Local(0)));
  return(1);

Text4:
  Message("%s: Jetzt hört doch auf zu Streiten, schaut lieber, wie wir da hinrüber kommen",Local(2),GetName(Local(2)));
  return(1);

Text5:
  Message("%s: Das muss durch dieses Loch in der Decke kommen. Wieso können die auch nie dichte Decken in ihre Minen machen!",Local(0),GetName(Local(0)));
  return(1);

Text6:
  Message("%s: Seht Ihr diese Sprengsätze? Damit könnten wir doch etwas sprengen, damit wir auf die andere Seite könnten.",Local(1),GetName(Local(1)));
  return(1);

Text7:
  Message("%s: Spreng du ruhig den Granit damit, jaja, dass wir alle begraben werden!",Local(0),GetName(Local(0)));
  return(1);

Text8:
  Message("%s: AH, seid doch still, ihr zwei ruiniert mir meine Nerven.",Local(2),GetName(Local(2)));
  return(1);

Fertig:
  RemoveObject();
  return(1);