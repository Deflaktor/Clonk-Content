#strict

Initialize:
  return(1);

MenuQueryCancel:
return(1);

Menu1:
  CreateMenu(MEN1,GetHiRank(),0,0,"Blut-Einstellungen",0,1);
  SetMenuSize(3,2,GetHiRank());
  AddMenuItem("Blut An","SetRainOn",MEN1,GetHiRank(),0,0,"Schaltet Blut an");
  AddMenuItem("Blut Aus","SetRainOff",MEN1,GetHiRank(),0,0,"Schaltet Blut aus");
  return(1);

Menu3:
  CreateMenu(MEN1,GetHiRank(),0,0,"Friendlyfire",0,1);
  SetMenuSize(3,2,GetHiRank());
  AddMenuItem("Friendlyfire an","FF1",MEN1,GetHiRank(),0,0,"Kugeln treffen Aliens und Clonks");
  AddMenuItem("Friendlyfire aus","FF0",MEN1,GetHiRank(),0,0,"Kugeln treffen keine Clonks");
  return(1);

Menu4:
  CreateMenu(MEN1,GetHiRank(),0,0,"Leben",0,1);
  SetMenuSize(3,6,GetHiRank());
  AddMenuItem("Keine","rnone",MEN1,GetHiRank(),0,0,"Stirbt der Clonk, ist der Spieler ebenfalls weg vom Fenster.");
  AddMenuItem("5","rfive",MEN1,GetHiRank(),0,0,"Der Spieler hat 5 Relaunches.");
  AddMenuItem("10","rten",MEN1,GetHiRank(),0,0,"Der Spieler hat 10 Relaunches.");
  AddMenuItem("20","rtwenty",MEN1,GetHiRank(),0,0,"Der Spieler hat 20 Relaunches.");
  AddMenuItem("50","rfifty",MEN1,GetHiRank(),0,0,"Der Spieler hat 50 Relaunches.");
  AddMenuItem("Unendlich","rinfinity",MEN1,GetHiRank(),0,0,"Der Spieler kann gar nicht verlieren.");
  SelectMenuItem(5,GetHiRank());
  return(1);

Menu5:
  CreateMenu(MEN1,GetHiRank(),0,0,"Schwierigkeitsgrad",0,1);
  SetMenuSize(3,4,GetHiRank());
  AddMenuItem("Leicht","Easy",MEN1,GetHiRank(),0,0,"Der Standard-Modus.");
  SelectMenuItem(  AddMenuItem("Mittel","Medium",MEN1,GetHiRank(),0,0,"Aliens sind von Anfang an vorhanden."),GetHiRank());
  AddMenuItem("Schwer","Hard",MEN1,GetHiRank(),0,0,"Doppelt so viele Aliens sind von Anfang an vorhanden.");
  AddMenuItem("Mörderisch","Harakiri",MEN1,GetHiRank(),0,0,"Dreimal so viele Aliens sind von Anfang an vorhanden.");
  return(1);

Menu6:
  CreateMenu(MEN1,GetHiRank(),0,0,"Gegnerstärke",0,1);
  SetMenuSize(3,4,GetHiRank());
  AddMenuItem("1/2","EasyUltra2",MEN1,GetHiRank(),0,0,"Alle Gegner sind halb so stark.");
  SelectMenuItem(  AddMenuItem("1-Fach","Easy2",MEN1,GetHiRank(),0,0,"Alle Gegner sind normal stark."),GetHiRank());
  AddMenuItem("1.5-Fach","Medium2",MEN1,GetHiRank(),0,0,"Alle Gegner sind 1.5 mal stärker.");
  AddMenuItem("2-Fach","Hard2",MEN1,GetHiRank(),0,0,"Alle Gegner sind doppelt so stark.");
  AddMenuItem("3-Fach","Harakiri2",MEN1,GetHiRank(),0,0,"Alle Gegner sind dreimal so stark.");
  AddMenuItem("4-Fach","SuperHarakiri2",MEN1,GetHiRank(),0,0,"Alle Gegner sind viermal so stark.");
  return(1);

Menu7:
  CreateMenu(MEN1,GetHiRank(),0,0,"Vermehrungsrate",0,1);
  SetMenuSize(3,3,GetHiRank());
  AddMenuItem("Sehr Langsam","rveryslow",MEN1,GetHiRank(),0,0,"Für Leute, die den Schwierigkeitsgrad Mörderisch erstmal antesten wollen.");
  AddMenuItem("Langsam","rslow",MEN1,GetHiRank(),0,0,"Langsame Alienvermehrung, ideal für Anfänger.");
  SelectMenuItem(  AddMenuItem("Mittel","rmedium",MEN1,GetHiRank(),0,0,"Standard-Einstellung, gut für standard-Clonker."),GetHiRank());
  AddMenuItem("Schnell","rfast",MEN1,GetHiRank(),0,0,"Wer den Helden spielen will, sollte das hier wählen. VORSICHT: Schneller Rechner empfohlen!");
  return(1);

Menu8:
  CreateMenu(MEN1,GetHiRank(),0,0,"Spielmodus",0,1);
  SetMenuSize(3,2,GetHiRank());
  SelectMenuItem(  AddMenuItem("Quest","nest",MEN1,GetHiRank(),0,0,"Spiele das Quest."),GetHiRank());
  AddMenuItem("Normal","nonest",MEN1,GetHiRank(),0,0,"Ganz normales Melee zwischen Aliens und Clonks");
  AddMenuItem("Quest Open Mode","nestOpenMode",MEN1,GetHiRank(),0,0,"Spiele das Quest ab dem Moment wo der Generator in Stand gesetzt worden ist.");
  return(1);

Menu9:
  CreateMenu(MEN1,GetHiRank(),0,0,"Superwaffen",0,1);
  SetMenuSize(3,2,GetHiRank());
  AddMenuItem("An","superwaffen",MEN1,GetHiRank(),0,0,"Redeemer, Schockwaveemitter, Nuker, Atomraketenpack, Verbesserte Schallpistole, Disruptor und Phaser Stufe 3 werden erscheinen.");
  AddMenuItem("Aus","nosuperwaffen",MEN1,GetHiRank(),0,0,"Gewöhnlicher Standard. Keine Superwaffen");
  return(1);

SetRainOn:
  SetGlobal(0,2);
  return(Menu4());

SetRainOff:
  SetGlobal(0,0);
  return(Menu4());

FF1:
  SetGlobal(17,1);
  return(Menu4());

FF0:
  SetGlobal(17,0);
  return(Menu4());

rnone:
  SetGlobal(10,1);
  SetGlobal(11,1);
  SetGlobal(12,1);
  SetGlobal(13,1);
  SetGlobal(14,0);
  return(Menu5());

rfive:
  SetGlobal(10,5);
  SetGlobal(11,5);
  SetGlobal(12,5);
  SetGlobal(13,5);
  SetGlobal(14,0);
  return(Menu5());

rten:
  SetGlobal(10,10);
  SetGlobal(11,10);
  SetGlobal(12,10);
  SetGlobal(13,10);
  SetGlobal(14,0);
  return(Menu5());

rtwenty:
  SetGlobal(10,20);
  SetGlobal(11,20);
  SetGlobal(12,20);
  SetGlobal(13,20);
  SetGlobal(14,0);
  return(Menu5());

rfifty:
  SetGlobal(10,50);
  SetGlobal(11,50);
  SetGlobal(12,50);
  SetGlobal(13,50);
  SetGlobal(14,0);
  return(Menu5());

rinfinity:
  SetGlobal(10,1);
  SetGlobal(11,1);
  SetGlobal(12,1);
  SetGlobal(13,1);
  SetGlobal(14,1);
  return(Menu5());

Easy:
  SetGlobal(3,0);
  return(Menu6());

Medium:
  SetGlobal(3,1);
  return(Menu6());

Hard:
  SetGlobal(3,2);
  return(Menu6());

Harakiri:
  SetGlobal(3,3);
  return(Menu6());

EasyUltra2:
  SetGlobal(4,-50);
  return(Menu7());

Easy2:
  SetGlobal(4,0);
  return(Menu7());

Medium2:
  SetGlobal(4,50);
  return(Menu7());

Hard2:
  SetGlobal(4,100);
  return(Menu7());

Harakiri2:
  SetGlobal(4,200);
  return(Menu7());

SuperHarakiri2:
  SetGlobal(4,300);
  return(Menu7());

rveryslow:
  SetGlobal(5,200);
  return(Menu8());

rslow:
  SetGlobal(5,150);
  return(Menu8());

rmedium:
  SetGlobal(5,100);
  return(Menu8());

rfast:
  SetGlobal(5,60);
  return(Menu8());

nest:
  SetGlobal(6,1);
  return(StartStoryGame());

nestOpenMode:
  SetGlobal(6,1);
  return(StartStoryGameOpenMode());

nonest:
  SetGlobal(6,0);
  return(Menu9());

superwaffen:
  var kokon; 
  SetGlobal(33,1);
  while (kokon=FindObject(_RDC, 0,0,0,0, 0, 0,0, 0, kokon)) {ChangeDef(_SP2,kokon);CreateContents(_ARP,kokon);}
  while (kokon=FindObject(RDC2, 0,0,0,0, 0, 0,0, 0, kokon)) And(ChangeDef(_SPW,kokon),CreateContents(RWP2,kokon));
  while (kokon=FindObject(RDC3, 0,0,0,0, 0, 0,0, 0, kokon)) {ChangeDef(_SPW,kokon);CreateContents(_KUT,kokon);}
  while (kokon=FindObject(RDC4, 0,0,0,0, 0, 0,0, 0, kokon)) And(ChangeDef(_SPW,kokon),CreateContents(_SWE,kokon));
  return(StartNormalGame());

nosuperwaffen:
  var kokon; 
  SetGlobal(33,0);
  while (kokon=FindObject(_RDC, 0,0,0,0, 0, 0,0, 0, kokon)) {ChangeDef(_SP2,kokon);CreateContents(_ARP,kokon);}
  while (kokon=FindObject(RDC2, 0,0,0,0, 0, 0,0, 0, kokon)) And(ChangeDef(_SPW,kokon),CreateContents(_HLR,kokon));
  while (kokon=FindObject(RDC3, 0,0,0,0, 0, 0,0, 0, kokon)) {ChangeDef(_SPW,kokon);CreateContents(DR1D,kokon);}
  while (kokon=FindObject(RDC4, 0,0,0,0, 0, 0,0, 0, kokon)) And(ChangeDef(_SPW,kokon),CreateContents(DR1D,kokon));
  while (kokon=FindObject(_GS1, 0,0,0,0, 0, 0,0, 0, kokon)) And(ChangeDef(_SPW,kokon),CreateContents(OZRK,kokon));
  while (kokon=FindObject(BOS2, 0,0,0,0, 0, 0,0, 0, kokon)) RemoveObject(kokon);
  return(StartNormalGame());
  
StartNormalGame:
  // Start Normal Game Mode
  Var(0)=FindObject(TG1_);
  Var(0)->ResetTarget();
  Var(0)->ResetTarget3();
  Var(0)->Trigger();
  // Remove all event handlers
  var container;
  var kokon; 
  while (kokon=FindObject(0, 0,0,0,0, 0, 0,0, 0, kokon)) if(ObjectCall(kokon,"IsEventHandler")) kokon->Enter(this());
  // Remove all generator spare parts
  kokon=0;
  while (kokon=FindObject(_COM, 0,0,0,0, 0, 0,0, 0, kokon)) kokon->Enter(this());
  CreateObject(_AKI);
  CreateObject(_RKI);
  return(Remove());
  
StartStoryGame:
  // Remove all normal spawn points
  while(Var(2)=FindObject(_SPW))
    RemoveObject(Var(2));
  // Start Story Game Mode
  Var(0)=FindObject(TG1_);
  Var(0)->ResetTarget2();
  Var(0)->ResetTarget3();
  Var(0)->Trigger();
  return(Remove());
  
StartStoryGameOpenMode:
  // Remove all normal spawn points
  while(Var(2)=FindObject(_SPW))
    RemoveObject(Var(2));
  // Start Story Game Mode
  Var(0)=FindObject(TG1_);
  Var(0)->ResetTarget2();
  Var(0)->Trigger();
  var obj=FindObject(_GEN);
  SetLocal(1,0,obj);
  SetLocal(2,0,obj);
  obj->SetAction("Running");
  return(Remove());
  

Remove:
  while(Var(0)=FindObject(GetID())) RemoveObject(Var(0));
  RemoveObject();
  return(1);