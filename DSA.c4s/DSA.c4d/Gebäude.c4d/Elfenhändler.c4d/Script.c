Initialize:
  SetAction("Wait");
  return(1);

ActivateEntrance:
  SetLocal(0,Par(0));
  SetCommand(Par(0),"none");
  if(SEqual(GetAction(),"Ready")) Call("Hallo","Sanya bha talar");
  return(1);

Hallo:
  Message("%s",this(),Par(0));
  Call("Auswahl1");
  return(1);

Auswahl1:
  SetAction("Wait");
  CreateMenu(0,Local(0),this());
  if(Equal(Local(1),0))  AddMenuItem("Was soll das heissen?","ElfischUnbekannt",YF3A,Local(0));
  if(Equal(Local(1),1))  AddMenuItem("Kannst du uns helfen?","Hilfe",YF3A,Local(0));

  if(Equal(Local(1),2))  AddMenuItem("Hast du uns Informationen?","Info",YF3A,Local(0));
  if(Equal(Local(1),2))  if(Equal(Local(3),0)) AddMenuItem("Kannst du uns etwas verkaufen?","Waffen",GD3A,Local(0));

  if(Equal(Local(2),1))  AddMenuItem("Bogen (10S)","Bogen",BO3A,Local(0));
  if(Equal(Local(2),1))  AddMenuItem("5 Normale Pfeile  (10S)","NormalePfeile",P13A,Local(0));
  if(Equal(Local(2),1))  AddMenuItem("5 Kriegspfeile  (20S)","Kriegspfeile",P63A,Local(0));
  if(Equal(Local(2),1))  AddMenuItem("1 Elfenpfeil  (75S)","Elfenpfeil",P53A,Local(0));
  if(Equal(Local(2),1))  AddMenuItem("1 Wirselkraut  (7S)","Wirselkraut",WK3A,Local(0));
  if(Equal(Local(2),1))  AddMenuItem("1 Kairan  (6S)","Kairan",KI3A,Local(0));
  if(Equal(Local(2),1))  AddMenuItem("1 Zaubertrank C  (8S)","ZaubertrankC",ZC3A,Local(0));

  return(1);

Kaufen:
  //Par(1) sind die Kosten, Par(0) ist der Artikel, Par(2) ist die Anzahl
  if(Not(Par(0))) return(0);
  if(Not(Par(1))) return(0);
  if(Not(Par(2))) return(0);
  SetWealth(0,Sub(GetWealth(0),Par(1)));
  Sound("uncash.wav");
  while( LessThan(ContentsCount(Par(0)),Par(2)))   CreateContents(Par(0));
  while(Contents())  Exit(Contents());
  return(1);
 
Bogen:
  if(LessThan(GetWealth(0),10)) Call("Hallo","Ihr habt nicht genug Geld.");
  if(GreaterThan(GetWealth(0),9)) Call("Kaufen",BO3A,10,1);
  return(1);

NormalePfeile:
  if(LessThan(GetWealth(0),10)) Call("Hallo","Ihr habt nicht genug Geld.");
  if(GreaterThan(GetWealth(0),9)) Call("Kaufen",P13A,10,5);
  return(1);

Kriegspfeile:
  if(LessThan(GetWealth(0),20)) Call("Hallo","Ihr habt nicht genug Geld.");
  if(GreaterThan(GetWealth(0),19)) Call("Kaufen",P63A,20,5);
  return(1);

Elfenpfeil:
  if(LessThan(GetWealth(0),75)) Call("Hallo","Ihr habt nicht genug Geld.");
  if(GreaterThan(GetWealth(0),74)) Call("Kaufen",P53A,75,1);
  return(1);

Wirselkraut:
  if(LessThan(GetWealth(0),7)) Call("Hallo","Ihr habt nicht genug Geld.");
  if(GreaterThan(GetWealth(0),6)) Call("Kaufen",WK3A,7,1);
  return(1);

Kairan:
  if(LessThan(GetWealth(0),6)) Call("Hallo","Ihr habt nicht genug Geld.");
  if(GreaterThan(GetWealth(0),5)) Call("Kaufen",KI3A,6,1);
  return(1);

ZaubertrankC:
  if(LessThan(GetWealth(0),8)) Call("Hallo","Ihr habt nicht genug Geld.");
  if(GreaterThan(GetWealth(0),7)) Call("Kaufen",ZC3A,8,1);
  return(1);




ElfischUnbekannt:
  SetLocal(1,1);
  Call("Hallo","Ich grüsse euch, Menschen.");
  return(1);

Hilfe:
  SetLocal(1,2);
  Call("Hallo","Das kommt darauf an.");
  return(1);

Info:
  Call("Hallo","Wenn Ihr etwas über das Leben lernen wollt, setzt Euch hin und lauschet der Natur, wenn Ihr anderes wissen wollt, fragt den Magier.");
  return(1);

Waffen:
  SetLocal(2,1);
  SetLocal(3,1);
  Call("Hallo","Ich kann euch Pfeile und Kräuter verkaufen");
  return(1);











AlleNull:
  SetLocal(0,0);
  SetLocal(1,0);
  SetLocal(2,0);
  SetLocal(3,0);
  SetLocal(4,0);
  SetLocal(5,0);
  SetLocal(6,0);
  SetLocal(7,0);
  SetLocal(8,0);
  SetLocal(9,0);
  return(1);
