#strict

Initialize:
  CreateContents(_I01);
  if(Equal(Random(4),0)) CreateContents(_I05);
  CreateContents(_G02);
  if(Equal(Random(4),0)) CreateContents(_I05);
  if(Equal(Random(4),0)) CreateContents(_I05);
  if(Equal(Random(4),0)) CreateContents(_I05);
  if(Equal(Random(4),0)) CreateContents(_I05);
  if(Equal(Random(4),0)) CreateContents(_I05);
  if(Equal(Random(4),0)) CreateContents(_I05);
  if(Equal(Random(4),0)) CreateContents(_I05);
  if(Equal(Random(3),0)) CreateContents(_I06);
  if(Equal(Random(3),0)) CreateContents(_I06);
  if(Equal(Random(2),0)) CreateContents(_I06);
  if(Equal(Random(2),0)) CreateContents(_I06);
 
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
  if(Not(SEqual(GetAction(),"Offen")))  Message("...Vielleicht besser öffnen...",this());
  return(1);

Inventar:
  //Enter(Local(0),Contents());
  Exit(Contents());
  return(1);
