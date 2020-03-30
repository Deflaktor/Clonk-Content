Initialize:
  SetAction("Wait");
  return(1);

ActivateEntrance:
  SetLocal(0,Par(0));
  SetCommand(Par(0),"none");
  if(SEqual(GetAction(),"Ready")) Call("Hallo","Kann ich Euch helfen?");
  return(1);

Hallo:
  Message("%s",this(),Par(0));
  Call("Auswahl1");
  return(1);

Auswahl1:
  SetAction("Wait");
  CreateMenu(0,Local(0),this());
  if(GreaterThan(Global(1),0))  if(Equal(Local(1),0))  AddMenuItem("Die Dorfbewohner schicken uns.","Dorf",_BGM,Local(0));

  if(Equal(Local(1),1))  AddMenuItem("Könnt Ihr uns etwas genaueres sagen?","Gegner",YF3A,Local(0));
  if(Not(Equal(Local(1),0)))  if(Equal(Local(2),0))  AddMenuItem("Was sollen wir tun?","Artefakte",YF3A,Local(0));

  if(Equal(Local(1),2))  AddMenuItem("Wo ist der Baron?","WoGegner",CST3,Local(0));
  if(Equal(Local(1),3))  AddMenuItem("Wie kommen wir dahin?","WiezumSchloss",YF3A,Local(0));

  if(Not(Equal(Local(2),0)))  AddMenuItem("Magische Tasche?","Tasche",MB3A,Local(0));

  if(Not(Equal(Local(2),0)))  AddMenuItem("Excalibur","Excalibur",EX3A,Local(0));
  if(Equal(Local(2),2))  AddMenuItem("Wo kriegen wir das Excalibur?","WoExcalibur",EX3A,Local(0));

  if(Not(Equal(Local(2),0)))  AddMenuItem("Zauberstab","Zauberstab",ZS3A,Local(0));
  if(Equal(Local(3),1))  AddMenuItem("Wo ist der Zauberstab?","WoZauberstab",ZS3A,Local(0));
  if(Equal(Local(3),2))  AddMenuItem("Sonst noch was?","Esse",_MES,Local(0));
  if(Equal(Local(3),3))  AddMenuItem("Wo sind diese Artefakte?","Heilig",_ZKR,Local(0));

  if(Not(Equal(Local(2),0)))  AddMenuItem("Elfenpfeile","Elfenpfeile",P53A,Local(0));
  if(Equal(Local(7),1))  AddMenuItem("Woher bekommen wir sie?","WoElfenpfeile",P53A,Local(0));

  if(Equal(Global(8),1)) if(Equal(Local(4),0)) AddMenuItem("Was sind das für Monolithen?","Monolith1",MN3A,Local(0));
  if(Equal(Local(4),1)) AddMenuItem("Wie benutzt man sie?","Monolith2",MN3A,Local(0));
  if(Equal(Local(4),2)) if(Equal(Local(5),0)) AddMenuItem("Und in die andere Richtung?","Monolith3a",MN3A,Local(0));
  if(Equal(Local(4),2)) if(Equal(Local(6),0)) AddMenuItem("Wo steht der Megamonolith?","Monolith3b",MM3A,Local(0));

  if(Equal(Local(1),4))  if(Equal(Local(4),2)) AddMenuItem("Hat der Baron einen Monolithen?","WegBaronFrei",MS3A,Local(0));


  return(1);

Gegner:
  SetLocal(1,2);
  Call("Hallo","Der Baron Gorubran ist sehr gefährlich. Ihr solltet Euch gut bewaffnen, bevor Ihr ihm gegenüber tretet!");
  return(1);

WoGegner:
  SetLocal(1,3);
  Call("Hallo","Er residiert in seiner Burg hoch in den Lüften.");
  return(1);

WiezumSchloss:
  SetLocal(1,4);
  Call("Hallo","Ich weiss es nicht, aber es muss einen Weg geben!");
  return(1);

Artefakte:
  SetLocal(2,1);
  Call("Hallo","Es gibt einige hilfreiche Artefakte in der Umgebung: Excalibur, die Elfenpfeile und den Zauberstab. Ausserdem schenke ich euch noch eine Magische Tasche.");
  CreateContents(MB3A,FindObject(MA3A));
  CreateContents(MB3A,FindObject(WL3A));
  CreateContents(MB3A,FindObject(KR3A));
  return(1);

Dorf:
  SetLocal(1,1);
  Call("Hallo","Aha, also geht es um den tyrannischen Baron.");
  return(1);

Tasche:
  Call("Hallo","Sie hat eine unbegrenzte Transportkapazität.");
  return(1);

Excalibur:
  SetLocal(2,2);
  Call("Hallo","Dies ist ein Zweihandschwert, welchem Kräfte zur Vernichtung von Gegnern wie auch zur Abwehr von Magie innewohnen.");
  return(1);

WoExcalibur:
  Call("Hallo","Ihr müsst den See im Westen überqueren und das Gewölbe dahinter durchsuchen.");
  return(1);

Zauberstab:
  SetLocal(3,1);
  Call("Hallo","Ein Magier erhält damit einen nie aufhörenden Zustrom von Magischer Energie.");
  return(1);

WoZauberstab:
  SetLocal(3,2);
  Call("Hallo","Er ist in einem Verliess nicht weit westlich von hier.");
  return(1);

Esse:
  SetLocal(3,3);
  Call("Hallo","Ja, Ihr bekommt den Zauberstab nur, wenn Ihr die drei heiligen Artefakte der Rondra, der Hesinde und des Ingerimms in die Magische Esse werft.");
  return(1);

Heilig:
  Call("Hallo","Gorubran besitzt auch diese Artefakte, seine Schergen bewachen sie, aber sie sind in der Nähe der Esse.");
  return(1);

Elfenpfeile:
  SetLocal(7,1);
  Call("Hallo","Es sind von den Elfen magische verstärkte Pfeile. Sie sind tödlich und unzerbrechlich.");
  return(1);

WoElfenpfeile:
  Call("Hallo","Ihr könnt sie überall finden. Sie werden in Truhen aufbewahrt.");
  return(1);

Monolith1:
  SetLocal(4,1);
  Call("Hallo","Die Monolithen sind das alte Transportmittel der Umgebung.");
  return(1);

Monolith2:
  SetLocal(4,2);
  Call("Hallo","Ihr könnt von jedem Monolithen zum MegaMonolithen kommen, indem ihr sie anfasst und euch darauf konzentriert.");
  return(1);

Monolith3a:
  SetLocal(5,1);
  Call("Hallo","Es gibt zu jedem Monolithen einen passenden Monostone, welcher auf das Gate geworfen werden muss.");
  return(1);

Monolith3b:
  SetLocal(6,1);
  Call("Hallo","Er soll unter dem alten Brunnen des Dorfes liegen, aber keiner ist sich sicher.");
  return(1);

WegBaronFrei:
  Call("Hallo","Ja, das könnte sein, Ihr müsst den Monostone dazu finden! Aber er ist sicher gut bewacht.");
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
