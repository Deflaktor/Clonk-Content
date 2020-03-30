Initialize:
  SetAction("Wait");
  return(1);

ActivateEntrance:
  SetLocal(0,Par(0));
  SetCommand(Par(0),"none");
  if(Not(Equal(Local(2),10))) if(Not(Equal(Local(1),10))) if(SEqual(GetAction(),"Ready")) Call("Hallo","Kommt Ihr, um mich zu befreien?");
  return(1);

Hallo:
  Message("%s",this(),Par(0));
  Call("Auswahl1");
  return(1);

Auswahl1:
  SetAction("Wait");
  CreateMenu(0,Local(0),this());
  if(GreaterThan(Global(5),0))  if(Equal(Local(2),0))  AddMenuItem("Dein Bruder schickt uns.","Bruderschick",_ZIV,Local(0));
  if(Equal(Global(5),1))  if(Equal(Local(2),0))  AddMenuItem("Zuerst: warum bist du gefangen?","DunkleVergangenheit",_GEF,Local(0));

  if(GreaterThan(Local(2),0))  if(LessThan(Local(2),3))  AddMenuItem("Wir glauben Dir.","Glauben",YJ3A,Local(0));
  if(Equal(Local(2),1))  AddMenuItem("Das soll die Wahrheit sein?","NichtGlauben",YN3A,Local(0));

  if(Equal(Local(2),2))  AddMenuItem("Bist du dir da ganz sicher?","NichtGlauben2",YF3A,Local(0));

  if(Equal(Local(2),3))  AddMenuItem("Nagut, immerhin tötest du die Richtigen.","Glauben",KS3A,Local(0));
  if(Equal(Local(2),3))  AddMenuItem("Mörder verdienen Ihre Strafe!","Mord",AXE1,Local(0));


  if(Equal(Global(5),0))  if(LessThan(Local(1),2))  AddMenuItem("Ja.","BefreiJa",YJ3A,Local(0));
  if(Equal(Global(5),0))  if(Equal(Local(1),0))  AddMenuItem("Nein.","BefreiNein",YN3A,Local(0));
  if(Equal(Global(5),0))  if(Equal(Local(1),0))  AddMenuItem("Wie kommst du darauf.","Warum",YF3A,Local(0));

  if(GreaterThan(Local(1),1))  AddMenuItem("Hast du uns Informationen?","Info",YF3A,Local(0));
  if(Equal(Local(1),2))  AddMenuItem("Bezahle uns!!","Geld",GD3A,Local(0));

  if(Equal(Local(1),3))  AddMenuItem("Ja.","Luegibuegi",YJ3A,Local(0));
  if(Equal(Local(1),3))  AddMenuItem("Nein, natürlich nicht","Entschuldigung",YN3A,Local(0));

  if(Equal(Local(1),4))  AddMenuItem("Akzeptiert.","PfeilGib",P63A,Local(0));
  if(Equal(Local(1),4))  AddMenuItem("Wo hast du die her?.","WoherPfeil",YF3A,Local(0));
  if(Equal(Local(1),4))  AddMenuItem("Wir wollen deine Pfeile nicht.","PfeilNein",YN3A,Local(0));
  return(1);

BefreiJa:
  SetLocal(1,2);
  Call("Hallo","Danke, kann ich euch irgendwie helfen?");
  return(1);

BefreiNein:
  Call("Hallo","Aber das könnt Ihr mir doch nicht antun. Ich bin unschuldig!");
  return(1);

Warum:
  SetLocal(1,1);
  Call("Hallo","Nun, Gerüchte besagen, dass Ihr gegen den Baron kämpft, ausserdem habt Ihr alle meine Bewacher getötet und meine Gefängnistüre geöffent.");
  return(1);

Info:
  Call("Hallo","Als Gefangener findet man nicht viel heraus, ich kann Euch nur sagen, dass Ihr Euch gut ausrüsten solltet, falls Ihr das noch nicht getan habt.");
  return(1);

Geld:
  SetLocal(1,3);
  Call("Hallo","Na hört mal, glaubt Ihr etwa, dass ich mehr als meine Kleider am Leib besitze?");
  return(1);

Luegibuegi:
  Call("Hallo","Das war eine rethorische Frage!!");
  return(1);

Entschuldigung:
  SetLocal(1,4);
  Call("Hallo","Nagut, ich will ja nicht so sein, Ihr könnt diese Pfeile haben, ich brauche sie nicht.");
  return(1);

WoherPfeil:
  Call("Hallo","Das will ich Euch nicht sagen, entweder Ihr nehmt sie oder nicht.");
  return(1);

Bruderschick:
  SetGlobal(5,4);
  SetLocal(2,10);
  Call("Hallo","Oh, wie schön, er wird euch sicher etwas schenken.");
  return(1);

DunkleVergangenheit:
  SetLocal(2,1);
  Call("Hallo","Zu Unrecht! Der Baron nahm mich als Geisel.");
  return(1);

Glauben:
  SetGlobal(5,4);
  SetLocal(2,10);
  Call("Hallo","Danke. Mein Bruder wird euch belohnen.");
  return(1);


NichtGlauben:
  SetLocal(2,2);
  Call("Hallo","Ich gebe es ja zu, bitte tut mir nichts. Ich habe einige Wachen umgebracht, aber nur, weil sie mich angriffen!");
  return(1);

NichtGlauben2:
  SetLocal(2,3);
  Call("Hallo","Fahrt doch zur Hölle, ich hab sie vergiftet!");
  return(1);

Mord:
  SetLocal(2,10);
  Call("Hallo","Welch Ironie, dass gerade IHR das sagt!");
  return(1);  

PfeilGib:
  SetLocal(1,10);
  CreateContents(P63A,Local(0));
  CreateContents(P63A,Local(0));
  CreateContents(P63A,Local(0));
  CreateContents(P63A,Local(0));
  CreateContents(P63A,Local(0));
  return(1);

PfeilNein:
  SetLocal(1,10);
  Call("Hallo","Selber schuld!");
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
