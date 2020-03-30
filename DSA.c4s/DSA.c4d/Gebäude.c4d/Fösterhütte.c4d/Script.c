#strict

Initialize:
  SetLocal(3,CreateContents(BERG));
  SetAction("Ready");
  return(1);

ActivateEntrance:
  SetLocal(0,Par(0));
  SetCommand(Par(0),"none");
  if(SEqual(GetAction(),"Ready")) {
    Sprich("Ja, was wollt ihr?");
    SetAction("Wait");
    Auswahl();
  }
  return(1);

Sprich:
  Message("%s",Local(3),Par(0));
  return(1);

Auswahl:
  CreateMenu(0,Local(0),this());
  if(Local(2)==0) 
    AddMenuItem("Wie können Sie mir dienen?","tach",_M01,Local(0));
  else {
    if(Local(1)&1&&!(FindObject(SLBT)||FindObject(SLBS)))  AddMenuItem("Ich brauche ein Boot.","boot",SLBT,Local(0));
    if(Local(1)&2)  AddMenuItem("Ich brauche eine Brücke.","bruecke",BRDG,Local(0));
  }
  AddMenuItem("Ich brauche nichts.","nichts",_M07,Local(0));
  SetAction("GetReady");
  return(1);

nichts:
  Sprich("Auf Wiedersehen!");
  SetAction("GetReady");
  return(1);

tach:
  Sprich("Ich kann verschiedene Dinge aus Holz herstellen. Was braucht ihr denn?");
  SetLocal(2,1);
  Auswahl();
  return(1);

boot:
  Sprich("Oh, sicherlich kann ich das machen, das würde 100 Gold kosten!");
  CreateMenu(0,Local(0),this());
  AddMenuItem("Ja ok.","bootKaufen",YJ3A,Local(0));
  AddMenuItem("Nein, das ist zuviel.","nichtKaufen",YN3A,Local(0));
  SetAction("GetReady");
  return(1);

bruecke:
  Sprich("Oh, sicherlich kann ich das machen, das würde 50 Gold kosten!");
  CreateMenu(0,Local(0),this());
  AddMenuItem("Ja ok.","brueckeKaufen",YJ3A,Local(0));
  AddMenuItem("Nein, das ist zuviel.","nichtKaufen",YN3A,Local(0));
  SetAction("GetReady");
  return(1);

nichtKaufen:
  Sprich("Tut mir Leid, aber ich kann nicht umsonst arbeiten.");
  SetAction("GetReady");
  return(1);

bootKaufen:
  if(Zahlen(100)) {
    Sprich("Ok geht klar, das Boot steht dann im See bereit, links vom Dorf.");
    SetVar(2,CreateObject(SLBT));
    SetPosition(1330,640,Var(2));
  } else {
    Sprich("Ohne Geld kein Boot.");
  }
  return(1);

brueckeKaufen:
  if(Zahlen(50)) {
    Sprich("Ok geht klar, warte schnell 10 Sekunden, bin gleich fertig.");
    SetAction("BrueckeBauen");
  } else {
    Sprich("Ohne Geld keine Bruecke.");
  }
  return(1);

brueckeFertig:
  Sprich("Hier, die Bruecke ist fertig, ich helf dir, sie zu transportieren.");
  SetLocal(4,CreateContents(BRDG));
  Exit(Local(4));
  Exit(Local(3));
  SetAction("BrueckeSetzen");
  return(1);

brueckeCheck:
  if(SEqual(GetAction(Local(4)),"Locked")) {
    Sprich("Ok, die Brücke sitzt. Ich mach mich dann wieder auf den Heimweg.");
    SetAction("Wait");
    SetCommand(Local(3),"MoveTo",this());
    AppendCommand(Local(3),"Call",this(),0,0,0,0,"ReinMitDir");
  } else {
    SetCommand(Local(3),"Grab",Local(4),30,0);
    if(Distance(GetX(Local(0)),GetY(Local(0)),GetX(Local(3)),GetY(Local(3)))>20)
      AppendCommand(Local(3),"PushTo",Local(4),GetX(Local(0))+30,GetY(Local(0)));
    SetVar(1,0);
    while (SetVar(0,FindObject(0,0,0,0,0,OCF_CrewMember(),"Push",Local(4),NoContainer(),Var(0))))
      if(Var(0)!=Local(3))
        SetVar(1,1);
    if(Var(1))
      SetCommand(Local(3),"MoveTo",0,GetX(Local(4))+30,GetY(Local(4)));
    if(GetX(Local(4))+30>4550) {
      SetComDir(COMD_None(), Local(3));
      SetCommand(Local(3), "");
    }
  }
  return(1);
  
ReinMitDir:
  Enter(this(),Local(3));
  SetAction("Ready");
  return(1);

Zahlen:
  if(GetWealth(0)>=Par(0)) {
    SetWealth(0,Sub(GetWealth(0),Par(0)));
    Sound("uncash.wav");
    return(1);
  }
  return(0);
