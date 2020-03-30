Initialize:
  SetAction("Wait");
  return(1);

ActivateEntrance:
  SetLocal(0,Par(0));
  SetCommand(Par(0),"none");
  if(SEqual(GetAction(),"Ready")) Call("Hallo","Benötigt Ihr meine magischen Kräfte?");
  return(1);

Hallo:
  Message("%s",this(),Par(0));
  Call("Auswahl1");
  return(1);

Auswahl1:
  SetAction("Wait");
  CreateMenu(0,Local(0),this(),0,"Keine wichtigen Gegenstände verloren bis jetzt.");
  if(Equal(Local(1),0))  AddMenuItem("Wie könntet Ihr uns helfen?","Frage",YF3A,Local(0));
  
  if(Equal(Local(1),1))  MenuItem(MB3A);
  if(Equal(Local(1),1))  MenuItem(KO3A);
  if(Equal(Local(1),1))  MenuItem(EX3A);
  if(Equal(Local(1),1))  MenuItem(ZS3A);
  if(Equal(Local(1),1))  MenuItem(MT3A);
  if(Equal(Local(1),1))  MenuItem(AC3A);
  if(Equal(Local(1),1))  MenuItem(BO3B);
  if(Equal(Local(1),1))  MenuItem(_RZS);
  if(Equal(Local(1),1))  MenuItem(_ZKI);
  if(Equal(Local(1),1))  MenuItem(_ZKR);
  if(Equal(Local(1),1))  MenuItem(_ZKH);

  return(1);

MenuItem:
  if(FindObject(Par(0),0,0,0,0,0,0,0,NoContainer()))
    return(AddMenuItem(GetName(0,Par(0)),"Beamen",Par(0),Local(0)));
  return(0);

Frage:
  SetLocal(1,1);
  Call("Hallo","Ich kann Euch Eure wichtigsten Gegenstände hierhin Teleportieren, falls Ihr sie verloren habt.");
  return(1);

Beamen:
  if(SetVar(1,FindObject(Par(0),0,0,0,0,0,0,0,NoContainer())))  Call("Erfolgreich",Var(1));
  if(Not(Var(1)))  Call("Misserfolg");
  return(1);

Erfolgreich:
  SetPosition(GetX(),Sum(GetY(),-10),Par(0));
  Message("Hier, bitte schön",this());
  return(1);

Misserfolg:
  Message("Entweder habt Ihr gar nichts verloren, oder es liegt ausserhalb meiner Macht.",this());
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
