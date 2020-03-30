Initialize:
  CreateContents(P53A);
  if(Equal(Random(4),0)) CreateContents(GD3A);
  if(Equal(Random(4),0)) CreateContents(GD3A);
  if(Equal(Random(4),0)) CreateContents(GD3A);
  if(Equal(Random(4),0)) CreateContents(GD3A);
  if(Equal(Random(3),0)) CreateContents(GS3A);
  if(Equal(Random(3),0)) CreateContents(GS3A);
  if(Equal(Random(2),0)) CreateContents(GS3A);
  if(Equal(Random(2),0)) CreateContents(GS3A);

  if(Equal(Random(6),0)) CreateContents(ZF3A);
  if(Equal(Random(2),0)) CreateContents(ZC3A);
  if(Equal(Random(4),0)) CreateContents(ZC3A);

  if(Equal(Random(7),0)) CreateContents(HE3A);
  if(Equal(Random(5),0)) CreateContents(HC3A);

  if(Equal(Random(2),0)) CreateContents(SP3A);
  if(Equal(Random(8),0)) CreateContents(OE3A);
  SetAction("Zu");
  return(1);

Bonus:
  //Par(0) ist der Artikel, Par(1) ist die Anzahl
  if(Not(Par(0))) return(0);
  if(Not(Par(1))) return(0);
  while( LessThan(ContentsCount(Par(0)),Par(1)))   CreateContents(Par(0));
  return(1);

ControlUp:
  SetAction("Offen");
  SetEntrance(1);
  return(1);

ControlDown:
  SetAction("Zu");
  SetEntrance(0);
  return(1);

ControlDig:
  SetLocal(0,Par(0));
  while(And(SEqual(GetAction(),"Offen") , Contents()))  Call("Inventar");
  if(Not(SEqual(GetAction(),"Offen")))  Message("Vielleicht sollte ich sie zuerst öffnen..",this());
  return(1);

Inventar:
  //Enter(Local(0),Contents());
  Exit(Contents());
  return(1);
