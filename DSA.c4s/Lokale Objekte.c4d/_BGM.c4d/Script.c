Initialize:
  SetAction("Wait");
  return(1);

ActivateEntrance:
  SetLocal(0,Par(0));
  SetCommand(Par(0),"none");
  if(SEqual(GetAction(),"Ready")) Call("Hallo","Habt ihr einen Moment Zeit?");
  return(1);

Hallo:
  Message("%s",this(),Par(0));
  Call("Auswahl1");
  return(1);

Auswahl1:
  SetAction("Wait");
  CreateMenu(0,Local(0),this());
  if(Equal(Local(1),0))  AddMenuItem("Ja.","AnfangKonversation",YJ3A,Local(0));
  if(Equal(Local(1),0))  AddMenuItem("Nein.","Abhauen",YN3A,Local(0));

  if(Not(Equal(Local(1),0)))  if(Equal(Local(2),0))  AddMenuItem("Inwiefern?","Weiter1",YF3A,Local(0));
  if(Not(Equal(Local(1),0)))  if(Equal(Local(2),1))  AddMenuItem("Ja?","Weiter2",YF3A,Local(0));
  if(Not(Equal(Local(1),0)))  if(Equal(Local(2),2))  AddMenuItem("Zum Beispiel?","Weiter3",YF3A,Local(0));
  if(Not(Equal(Local(1),0)))  if(Equal(Local(2),3))  AddMenuItem("Wieso wehrt ihr euch denn nicht?","Weiter4",YF3A,Local(0));
  if(Not(Equal(Local(1),0)))  if(Equal(Local(2),4))  AddMenuItem("Und was haben wir damit zu tun?","Weiter5",YF3A,Local(0));

  if(Equal(Local(2),5))  if(Equal(Local(3),0))  AddMenuItem("Und was springt für uns dabei raus?","Belohnung",YF3A,Local(0));
  if(Equal(Local(2),5))  AddMenuItem("Ja, wir helfen euch","AuftragAccept",YJ3A,Local(0));
  if(Equal(Local(2),5))  AddMenuItem("Vergiss es!","Abhauen",YN3A,Local(0));
  if(Equal(Local(2),6))  AddMenuItem("Wo sollten wir anfangen?","Magier",_MAG,Local(0));
  if(Equal(Local(2),7))  AddMenuItem("Wo finden wir ihn?","WoMagier",_MAG,Local(0));
  if(GreaterThan(Local(2),5))  if(Equal(Local(4),0)) AddMenuItem("Und wie sollen wir uns denn Bewaffnen?","Waffen",YF3A,Local(0));

  return(1);

AnfangKonversation:
  SetLocal(1,1);
  Call("Hallo","Wir brauchen eure Hilfe: Der Baron Gorubran macht uns Schwierigkeiten.");
  return(1);

Weiter1:
  SetLocal(2,1);
  Call("Hallo","Naja, er terrorisiert unser Dorf.");
  return(1);

Weiter2:
  SetLocal(2,2);
  Call("Hallo","Er erniedrigt uns!");
  return(1);

Weiter3:
  SetLocal(2,3);
  Call("Hallo","Er zwingt uns zum Beispiel, in den Minen zu schuften!");
  return(1);

Weiter4:
  SetLocal(2,4);
  Call("Hallo","Weil er eine grosse Armee von Kriegern hat und ausserdem geht das Gerücht von einem Dämon um.");
  return(1);

Weiter5:
  SetLocal(2,5);
  Call("Hallo","Ihr sollt ihn stellen und dazu zwingen, uns in Ruhe zu lassen.");
  return(1);

Belohnung:
  SetGlobal(9,Sum(Global(9),400));
  Sound("cash.wav");
  SetLocal(3,1);
  Call("Hallo","Wir haben nicht viel, aber ihr bekommt je 400 Dukaten");
  return(1);

AuftragAccept:
  SetGlobal(1,1);
  SetLocal(2,6);
  Call("Hallo","Seid von den Göttern gesegnet!");
  return(1);

Magier:
  SetLocal(2,7);
  Call("Hallo","Der Magier bei den Elfen kann euch sicher weiterhelfen");
  return(1);

WoMagier:
  Call("Hallo","Die Elfensiedlung ist auf dem Berg im Osten, seid vorsichtig und geht noch nicht in die Minen.");
  return(1);

Waffen:
  SetLocal(4,1);
  CreateObject(KP3A);
  CreateObject(AXE1);

//Heil- und Zaubertränke
  CreateObject(ZF3A);
  CreateObject(ZF3A);
  CreateObject(ZF3A);
  CreateObject(ZC3A);
  CreateObject(ZC3A);
  CreateObject(HE3A);
  CreateObject(HC3A);
  CreateObject(HC3A);

//Bogen, Köcher und Pfeile
  CreateObject(BO3A);
  SetVar(0,CreateObject(KO3A));
  CreateContents(P13A,Var(0));
  CreateContents(P13A,Var(0));
  CreateContents(P13A,Var(0));
  CreateContents(P13A,Var(0));
  CreateContents(P13A,Var(0));
  CreateContents(P13A,Var(0));
  CreateContents(P13A,Var(0));
  CreateContents(P13A,Var(0));
  CreateContents(P13A,Var(0));
  CreateContents(P13A,Var(0));
  CreateContents(P63A,Var(0));
  CreateContents(P63A,Var(0));
  CreateContents(P63A,Var(0));
  CreateContents(P63A,Var(0));
  CreateContents(P63A,Var(0));
  Call("Hallo","Ich werde euch einige beschaffen. | - | Hier.");
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

Abhauen:
  SetLocal(9,Sum(Local(9),1));
  if(LessThan(Local(9),4))   Call("Hallo","Wollt Ihr euch das nicht noch einmal überlegen?");
  if(GreaterThan(Local(9),3))  Call("Hallo","Bitte!");
  if(GreaterThan(Local(9),5))  Call("Hallo","Ihr müsst mir helfen!");
  if(GreaterThan(Local(9),7))  Call("Hallo","Wir schweben alle in Lebensgefahr!");
  if(Equal(Local(9),10))  if(SetGlobal(9,Sum(Global(9),100)))    if(Sound("cash.wav"))    Call("Hallo","Wir bezahlen euch auch gut! | +100 Dukaten");
  if(GreaterThan(Local(9),10))  Call("Hallo","Helft uns!!!");
  if(GreaterThan(Local(9),15))  Call("Hallo","*Winsel* BBBBIIIIIIIITTTTTTTTTTTEEEEEEEEE!!!!!!");
  if(GreaterThan(Local(9),81))  Call("Hallo","Wer das hier liest hat entweder eine Riesengeduld oder schaut im Script nach. *smile* ");
  if(GreaterThan(Local(9),82))  Call("Hallo","Scripts By Kdansky");
  if(GreaterThan(Local(9),83))  Call("Hallo","Most Graphics by Fabian");
  if(GreaterThan(Local(9),84))  Call("Hallo","Many Graphics by Kdansky");
  if(GreaterThan(Local(9),85))  Call("Hallo","Some Graphics by Patrik");
  if(GreaterThan(Local(9),86))  Call("Hallo","Story, Landscape and Idea by Kdansky");
  if(GreaterThan(Local(9),89))  Call("Hallo","Wenn Ihr wirklich nicht wollt, seid Ihr gar keine Helden.");
  if(GreaterThan(Local(9),90))  Call("Dannhaltnicht");
  return(1);

Dannhaltnicht:
  Call("Hallo","Wenn Ihr nicht wollt, dann könnt ihr gehen, ihr seid keine echten Helden!");
  Explode(130,this());
  while(SetVar(0,FindObject(0,0,0,-1,-1,OCF_CrewMember()))) Explode(10,Var(0));
  GameOver();
  return(1);

