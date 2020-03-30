Initialize:
  SetAction("Wait");
  return(1);

ActivateEntrance:
  SetLocal(0,Par(0));
  SetCommand(Par(0),"none");
  if(Not(Equal(Local(1),4)))  if(SEqual(GetAction(),"Ready")) Call("Hallo","Helft uns!");
  if(Equal(Local(1),4))  if(SEqual(GetAction(),"Ready")) Call("Hallo","Habt Ihr ihn schon gefunden?");
  return(1);

Hallo:
  Message("%s",this(),Par(0));
  Call("Auswahl1");
  return(1);

Auswahl1:
  SetAction("Wait");
  if(Not(Equal(Local(1),10))) CreateMenu(0,Local(0),this());
  if(Equal(Local(1),0))  AddMenuItem("Wie denn?","Start",YF3A,Local(0));
  if(Equal(Local(1),0))  AddMenuItem("Halt die Klappe!","Klappe",YF3A,Local(0));

  if(Equal(Local(1),1))   AddMenuItem("Sonst noch was?","NochWas",YF3A,Local(0));
  if(Equal(Local(1),2))   AddMenuItem("Ja","HelfJa1",YJ3A,Local(0));
  if(Equal(Local(1),2))   AddMenuItem("Nein","Klappe",YN3A,Local(0));
  if(Equal(Local(1),2))   AddMenuItem("Wieso wurde er eingesperrt?","HelfWarum",_GEF,Local(0));

  if(Equal(Local(1),3))   AddMenuItem("Nagut!","HelfJa2",YJ3A,Local(0));
  if(Equal(Local(1),3))   AddMenuItem("Niemals!","Klappe",YN3A,Local(0));

  if(Equal(Local(1),4))  if(Not(Equal(Global(5),4)))   AddMenuItem("Nein, wir waren erfolglos.","Erfolglos",YN3A,Local(0));
  if(Equal(Local(1),4))  if(Equal(Global(5),4))   AddMenuItem("Ja.","Belohnung",YJ3A,Local(0));
  return(1);

Start:
  SetLocal(1,1);
  Call("Hallo","Der Baron Gorubran terrorisiert uns. Unser Bürgermeister kann euch sicher genaueres sagen!");
  return(1);

Klappe:
  Call("Hallo","Und sowas nennt sich Held!!!! Pah!!!");
  return(1);

NochWas:
  SetLocal(1,2);
  Call("Hallo","Ja, Gorubran hat meinen Bruder entführt, könntet Ihr ihn retten?");
  return(1);

HelfJa1:
  SetLocal(1,4);
  SetGlobal(5,2);
  Call("Hallo","Danke, ich hoffe, Ihr kommt bald wieder!");
  return(1);

HelfJa2:
  SetLocal(1,4);
  SetGlobal(5,1);
  Call("Hallo","Danke.");
  return(1);

HelfWarum:
  SetLocal(1,3);
  Call("Hallo","Ähm... naja... Ich weiss es doch auch nicht so genau, aber bitte helft!");
  return(1);

Erfolglos:
  Call("Hallo","Bitte sucht weiter!!");
  return(1);

Belohnung:
  SetWealth(0,Sum(GetWealth(0),50));
  SetLocal(1,10);
  Sound("cash.wav");
  Call("Hallo","Wie mich das freut, hier habt Ihr eine Belohnung||(+50S)");
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
