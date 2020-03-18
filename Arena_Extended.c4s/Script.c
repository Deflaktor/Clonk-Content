/****-- ARENA --****/

#strict

/*-- Szenario beginnt --*/
Initialize:
  DrawMaterialQuad("Granite-Rough",0,LandscapeHeight()-42,LandscapeWidth(),LandscapeHeight()-42,LandscapeWidth(),LandscapeHeight(),0,LandscapeHeight());
  SetClimate(50);
  SetGamma(RGB(0,0,0),RGB(127,127,127),RGB(255,255,255));
  ScriptGo(1);
  MusicLevel(100-MusicVolume());
  Global(3)=5;
  return(0);

MusicVolume:
  return(100-30);

DebugMode:
  SetWealth(Par(0),10000);
  return(1);
  
GetXPosition:
  return(GetX(Par(0)));

GetYPosition:
  return(GetY(Par(0)));

/*-- Neuer Spieler --*/
InitializePlayer:
  SetOwner(Par(0),CreateObject(SDCL,10,10));
  //DebugMode(Par(0));
  JoinPlayer(Par(0));
  return(0);

Test:
  ObjectCall(FindObject(CLON),"Respawn");
  return();

/*-- Respawn eines alten --*/
RelaunchPlayer:
  if(Not(GetPlayerName(Par(0)))) return(0);
  //Spieler wird aus der Luft abgeworfen
  ObjectCall(Par(1),"Respawn");
  //MakeCrewMember(Par(1),Par(0));
  //Sichtbares Bild sofort auf den neuen Spieler zentrieren
  SetCursor(Par(0),GetCrew(Par(0)));
  //damit jeder nachlesen kann wer gerade neu kommt:
  SetVar(1,Random(4));
  if(Equal(Var(1),0)) Log("Komm schon %s",GetPlayerName(Par(0)));
  if(Equal(Var(1),1)) Log("%s muss respawnen, tsts",GetPlayerName(Par(0)));
  if(Equal(Var(1),2)) Log("%s meinte fliegen zu können",GetPlayerName(Par(0)));
  if(Equal(Var(1),3)) Log("Re %s",GetPlayerName(Par(0)));
  //JoinPlayer aufrufen
  JoinPlayer(Par(0));
  return(0);

/*-- Spieler tritt bei (neu bzw wieder)--*/
JoinPlayer:
  //sounds dürfen nicht fehlen
  Sound("PlayerJoin");
  //alte Kisten zerstören (öh ist ganz bestimmt nich von Hazard nachgemacht)
  while(SetVar(0,FindObject(CHST,0,0,0,0,0,0,0,0,Var(0)))) if(Equal(GetOwner(Var(0)),Par(0))) RemoveObject(Var(0));
  while(SetVar(0,FindObject(_LIV,0,0,0,0,0,0,0,0,Var(0)))) if(Equal(GetOwner(Var(0)),Par(0))) RemoveObject(Var(0));
  while(SetVar(0,FindObject(CG1K,0,0,0,0,0,0,0,0,Var(0)))) if(Equal(GetOwner(Var(0)),Par(0))) RemoveObject(Var(0));
  while(SetVar(0,FindObject(RJET,0,0,0,0,0,0,0,0,Var(0)))) if(Equal(GetOwner(Var(0)),Par(0))) RemoveObject(Var(0));
  while(SetVar(0,FindObject(RJTA,0,0,0,0,0,0,0,0,Var(0)))) if(Equal(GetOwner(Var(0)),Par(0))) RemoveObject(Var(0));
  //er möchte ja kaufen können
  SetOwner(Par(0),CreateContents(CHST,GetCrew(Par(0))));
  //Seine Energieanzeige
  CreateObject(_LIV,0,0,Par(0));
  //Spieler wird aus der Luft abgeworfen
  SetPosition(Random(LandscapeWidth()),0,GetCrew(Par(0)));
  return(0);

LandschaftWiederherstellen:
  goto(1500);
  return(1);

Script1500:
  if(FindObject(REEH)) {
    Sound("EventDo");
    Message("Die Erde kommt zurück!");
    SetVar(0,FindObject(EVT_));
    SetLocal(1,(Local(0,Var(0))*-3)+36+22,Var(0));
    if(!Random(5))
      RestoreMapInstantly();
    else
      RestoreMap1();
  }
  return(1);

Script1700:  
  RestoreMap2();
  return(1);

Script1720:  
  Message("Die Erde kommt nicht mehr!");
  goto(1);
  return(1);

Event:
  var letzteEventID = 41;
  var threattype = Random(letzteEventID+1+10);
  // Die ersten 10 Events haben doppelte wahrscheinlichkeit
  threattype = threattype % (letzteEventID+1);

  // Seltene Events:
  Sound("EventDo");
  if((threattype == 35 || threattype == 36 || threattype == 39) && !Random(2))
    return(Event());
  GameCall(Format("Event%d",threattype));
  return(1);

Event0:
Message("Totale Kamikaze Action!");
for(var i = 0; i<5; i++)
 SetPosition(Random(LandscapeWidth()),0,CreateObject(GIK1,0,0,-1));
return(1);

Event1:
Message("Ein bisschen Eke?");
for(var i = 0; i<5; i++)
 SetPosition(Random(LandscapeWidth()),0,CreateObject(MF5B,0,0,-1));
return(1);

Event2:
Message("Klassische Gegner!");
for(var i = 0; i<10; i++)
 SetPosition(Random(LandscapeWidth()),0,CreateObject(KI58,0,0,-1));
return(1);

Event3:
Message("Mixen macht Laune!");
for(var i = 0; i<9; i++)
 {
 SetPosition(Random(LandscapeWidth()),0,CreateObject(RandomEnemy(),0,0,-1));
 }
return(1);

Event4:
Message("Jipie! Eine Statue!");
SetPosition(Random(LandscapeWidth()),0,CreateObject(ASDF,0,0,-1));
return(1);

Event5:
Message("Was? Ein Gigantischer Kami-Kaze?");
SetPosition(Random(LandscapeWidth()),0,CreateObject(BIG1,0,0,-1));
return(1);

Event6:
Message("Ein paar winzige Kami-Kaze!");
for(var i = 0; i<10; i++)
 SetPosition(Random(LandscapeWidth()),0,CreateObject(WIG1,0,0,-1));
return(1);

Event7:
Message("BOMBENHAGEL!!!");
for(var i = 0; i<100; i++)
 SetPosition(Random(LandscapeWidth()),0,CreateObject(_WSP,0,0,-1));
return(1);

Event8:
Message(Format("%d Rambos!", Global(3)));
for(var i = 0; i<Global(3); i++)
 SetPosition(Random(LandscapeWidth()),0,CreateObject(C158,0,0,-1));
if(!Par(0))
  Global(3)++;
return(1);

Event9:
Message("Pfeil und Bogen gegen Flints!");
for(var i = 0; i<10; i++)
 SetPosition(Random(LandscapeWidth()),0,CreateObject(KB3A,0,0,-1));
return(1);

Event10:
Message("Monstergeddon!");
for(var i = 0; i<3; i++)
SetOwner(-1,CreateObject(_MGD,Random(LandscapeWidth()),Random(LandscapeHeight())));
return(1);

Event11:
Message("Apokalypse!!!");
ObjectSetAction(CreateObject(NEBB,LandscapeWidth()-300,0,-1),"Activated");
ObjectSetAction(CreateObject(NEBB,300,0,-1),"Activated");
return(1);

Event12:
Message("Flummiland");
for(var i = 0; i<10; i++)
 SetPosition(Random(LandscapeWidth()),0,CreateObject(FF4V,0,0,-1));
for(var i = 0; i<10; i++)
 SetPosition(Random(LandscapeWidth()),0,CreateObject(JU58,0,0,-1));
for(var i = 0; i<10; i++)
 SetPosition(Random(LandscapeWidth()),0,CreateObject(_AUS,0,0,-1));
return(1);

Event13:
Message("Halluzinationen PUR!");
for(var i = 0; i<15; i++)
 SetPosition(Random(LandscapeWidth()),0,CreateObject(HNTF,0,0,-1));
return(1);

Event14:
Message("Achtung: Fallen!");
for(var i = 0; i<3; i++)
 ObjectSetAction(CreateObject(FA_3,Random(LandscapeWidth()),0,-1),"Gestellt");
return(1);

Event15:
var i;
Message("Napalm-Angriff!");
for(i = 0; i<LandscapeWidth()/15; i++)
 CreateObject(DFL2,i*15,i*(-10),-1);
return(1);

Event16:
Message("Betonesel Angriff!");
for(var i = 0; i<5; i++)
 CreateObject(ESEL,Random(LandscapeWidth()),0,-1);
return(1);

Event17:
Message("Armageddon!!!");
CreateObject(_AMA,0,0,-1);
return(1);

Event18:
Message("Shockwave Wave!");
// CastObjects(SHFT,10,300,LandscapeWidth()/2,100);
 CreateObject(SJ3V,LandscapeWidth()/2,100,-1);
return(1);

Event19:
  Message("Gravitationsstoß!");
  CreateObject(_GNS,0,0,-1);
  return(1);

Event20:
Message("Flintregen!");
CreateObject(_FTS,0,0,-1);
return(1);

Event21:
Message("Shockwave Wave Waves Waver!");
for(var i = 0; i<5; i++)
{
for(;SkyGet();)
{}
CreateObject(SJ3V,Global(1),Global(2),-1);
}
return(1);

Event22:
if(FindObject(SRKR))
  return(Event());
Message("Schwarzes-Loch-Runde!");
for(var i=0; i<GetPlayerCount(); i++) SetOwner(i,CreateContents(SLGR,GetCursor(i)));
return(1);

Event23:
Message("Huh???");
for(var i=0; i<GetPlayerCount(); i++) 
  SetOwner(-1,CreateContents(C158,GetCursor(i)));
return(1);

Event24:
Message("Bombeneinheit");
while(SetVar(0,FindObject(0,0,0,0,0,OCF_Collectible(),0,0,0,Var(0)))) 
  if(GetID(Var(0))!=CHST)
    ChangeDef(SHFT,Var(0));
return(1);

Event25:
Message("Ein bombiges Event");
SetPosition(Random(LandscapeWidth()),0,CreateObject(BGBM,0,0,-1));
return(1);

Event26:
Message("Gott segnet euch mit Geld!");
SetPosition(Random(LandscapeWidth()),0,CreateObject(RGSS,0,0,-1));
return(1);

Event27:
Message("Der Teufel verflucht euch mit Geld!");
SetPosition(Random(LandscapeWidth()),0,CreateObject(RSSS,0,0,-1));
return(1);

Event28:
Message("Schallwellen Welle");
for(;SkyGet();)
{}
CreateObject(SJ4V,Global(1),Global(2),-1);
return(1);

Event29:
if(FindObject(SRKR))
  return(Event());
Message("Raumkrümung durch Schwarze Löcher");
for(var i = 0; i<3; i++)
SetOwner(-1,CreateObject(_SLC,Random(LandscapeWidth()),Random(LandscapeHeight()),-1));
return(1);

Event30:
Message("BONUS RUNDE!!!");
for(var i = 0; i<50; i++)
 {
 var threattype2 = Random(5);
 if(threattype2<5)
  SetPosition(Random(LandscapeWidth()),0,CreateObject(ST58,0,0,-1));
 if(threattype2==5)
  SetPosition(Random(LandscapeWidth()),0,CreateObject(S582,0,0,-1));
 }
return(1);

Event31:
Message("Hol dir das Equipment!");
SetOwner(-1,CreateObject(_EQP,50+Random(LandscapeWidth()-100),50+Random(LandscapeHeight()-140),-1));
return(1);

Event32:
Message("Pokemon Kampf!");
for(var i = 0; i<5; i++) {
  SetPosition(Random(LandscapeWidth()),0,Var(0)=CreateObject(KIL2,0,0,-1));
  Var(0)->SetWeapID(P57M);
}
for(var j=0; j<4; j++)
  for(var i=0; i<GetPlayerCount(); i++) SetOwner(i,CreateContents(P57M,GetCursor(i)));
return(1);

Event33:
if(FindObject(SRKR))
  return(Event());
Message("Remover Runde");
while(SetVar(0,FindObject(0,0,0,0,0,OCF_Collectible(),0,0,0,Var(0)))) 
if(GetID(Var(0))!=CHST)
  ChangeDef(_MFF,Var(0));
return(1);

Event34:
Message("Die Ärzte kommen!");
for(var i = 0; i<15; i++) {
 SetPosition(Random(LandscapeWidth()),0,Var(0)=CreateObject(KIL1,0,0,-1));
 Var(0)->SetWeapID(KREI);
 Var(0)->SetColor(9);
}
return(1);

Event35:
Message("Die Raymen mit der heiligen Granate greifen an!");
for(var i = 0; i<10; i++) {
 SetPosition(Random(LandscapeWidth()),0,Var(0)=CreateObject(DIL1,0,0,-1));
 Var(0)->SetWeapID(KAC5);
 Var(0)->SetColorDw(RGBa(0,0,0,255));
}
return(1);

Event36:
Message("Countdown für göttliche Vergeltung beginnt!");
CreateObject(_GVD);
return(1);

Event37:
Message("Schwere Infanterie.");
for(var i = 0; i<5; i++) {
 SetPosition(Random(LandscapeWidth()),0,Var(0)=CreateObject(KIL1,0,0,-1));
 Var(0)->SetWeapID(Zufallsflint2());
 Var(0)->SetColorDw(RGBa(255,0,0,0));
 Var(0)->SetClrModulation(RGBa(170,50,50,0));
 Var(0)->SetPhysical("Walk",40000,2);
}
return(1);

Event38:
Message("Geister!");
for(var i = 0; i<2; i++) {
 SetPosition(Random(LandscapeWidth()),0,Var(0)=CreateObject(KIK1,0,0,-1));
 Var(0)->SetClrModulation(RGBa(50,50,50,230));
 //Var(0)->SetPhysical("Walk",150000,2);
}
for(var i = 0; i<5; i++) {
 SetPosition(Random(LandscapeWidth()),0,Var(0)=CreateObject(KIL1,0,0,-1));
 Var(0)->SetClrModulation(RGBa(50,50,50,230));
// Var(0)->SetPhysical("Walk",100000,2);
}
return(1);

Event39:
Message("Wololo!");

for(var j=0; j<10; j++)
  for(var i=0; i<GetPlayerCount(); i++) SetOwner(i,CreateContents(JU59,GetCursor(i)));

var l=20;

while(SetVar(0,FindObject(0,0,0,0,0,OCF_Collectible(),0,0,0,Var(0)))&&l>=0) 
  if(GetID(Var(0))!=CHST) {
    ChangeDef(JU59,Var(0));
    l--;
  }

Var(0)=0;

while(SetVar(0,FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,0,Var(0)))) 
  if(GetID(Var(0))==KIL1||GetID(Var(0))==KIK1) {
    Var(0)->SetWeapID(JU59);
  }

for(var i = 0; i<5; i++) {
 SetPosition(Random(LandscapeWidth()),0,Var(0)=CreateObject(KIL1,0,0,-1));
 Var(0)->SetWeapID(JU59);
}
return(1);

Event40:
Message("Platztausch!");
Sound("capeopen");
	var count,repeat;
	count=ObjectCount(0,0,0,0,0,OCF_CrewMember()|OCF_Alive());
	count-=ObjectCount(GIK1);
	count-=ObjectCount(BIG1);
	count-=ObjectCount(WIG1);
	repeat = count*2;
	var firstObj, secondObj;
	//for(var i=0;i<repeat;i++) {
	  while(secondObj = FindObject(0,0,0,0,0,OCF_CrewMember()|OCF_Alive(),0,0,0,secondObj)) {
	    if(GetCon(secondObj)!=100) continue;
	    if(firstObj) {
		  SwapTwoObjects(firstObj,secondObj);
		}
		firstObj = secondObj;
	  }
	//}
return(1);

Event41:
Message("Keine Grenzen!");
CreateObject(_NOB,0,0,-1);
return(1);

public func SwapTwoObjects(object obj, object obj2) {
  var x,y,r,xdir,ydir,rdir,action,phase;
  x=GetX(obj);
  y=GetY(obj);
  r=GetR(obj);
  xdir=GetXDir(obj);
  ydir=GetYDir(obj);
  rdir=GetRDir(obj);
  action=obj->GetAction();
  phase=obj->GetPhase();
  obj->SetPosition(GetX(obj2),GetY(obj2));
  obj->SetR(GetR(obj2));
  obj->SetXDir(GetXDir(obj2));
  obj->SetYDir(GetYDir(obj2));
  obj->SetRDir(GetRDir(obj2));
  obj->SetAction(obj2->GetAction());
  obj->SetPhase(obj2->GetPhase());
  obj2->SetPosition(x,y);
  obj2->SetR(r);
  obj2->SetXDir(xdir);
  obj2->SetYDir(ydir);
  obj2->SetRDir(rdir);
  obj2->SetAction(action);
  obj2->SetPhase(phase);
}


RandomEnemy:
  var i=Random(10);
  if(i==0) return(KI58);
  if(i==1) return(DIL1);
  if(i==2) return(KIK1);
  if(i==3) return(GIK1);
  if(i==4) return(KB3A);
  if(i==5) return(KIL1);
  if(i==6) return(WIG1);
  if(i==7) return(MF5B);
  if(i==8) return(MONS);
  return(C158);
  

EarthMaterials:
if(Equal(GetMaterial(SetVar(0,Random(LandscapeWidth())),SetVar(1,Random(LandscapeHeight()))),Material("Earth")))
{
SetVar(0,CreateObject(CTOT,Var(0),Var(1)));
ObjectCall(Var(0),"Init",Par(0));
return(1);
}
return(0);

SkyGet:
var x,y;
x=Random(LandscapeWidth()-10)+10;
y=Random(LandscapeHeight()-200)+10;
if(GetMaterial(x,y) != Material("Sky")) 
{
return(1);
}
else
{
SetGlobal(1,x);
SetGlobal(2,y);
return(0);
}
return(1);

RestoreMap1: 
SetTemperature(-100);
return(1);

RestoreMap2: 
SetTemperature(100);
return(1);

RestoreMapInstantly: 
  DrawDefMap(0,0,LandscapeWidth(), LandscapeHeight(), "Arena");
  if(!FindObject(_NOB))
    DrawMaterialQuad("Granite-Rough",0,LandscapeHeight()-42,LandscapeWidth(),LandscapeHeight()-42,LandscapeWidth(),LandscapeHeight(),0,LandscapeHeight());
  Message("Erde wiederhergestellt!");
  goto(1);
  return(1);
  
DrawFlintQuad: 
  DrawDefMap(Par(0),Par(1),Par(2), Par(3), "FlintStone");
  if(!FindObject(_NOB))
    DrawMaterialQuad("Granite-Rough",0,LandscapeHeight()-42,LandscapeWidth(),LandscapeHeight()-42,LandscapeWidth(),LandscapeHeight(),0,LandscapeHeight());
  return(1);
 
RestoreMapLineByLine: 
  var x,y;
  Global(0)++;
  if(Global(0)==LandscapeWidth())
    Global(0)=0;
  x=Global(0);
  for(y=0;y<LandscapeHeight();y++)
    if (GetMaterial(x,y) == Material("Tunnel")) 
      DrawMaterialQuad ("Earth-Rough", x, y, x, y, x+1, LandscapeHeight()-42, x, y, 1);
  return(1);

Zufallsflint:
SetVar(0,Random(22));
  if(!Random(1300)) return(SRST);
  if(Equal(Var(0),0)) return(MARI);
  if(Equal(Var(0),1)) return(WBOB);
  if(Equal(Var(0),2)) return(BALL);
  if(Equal(Var(0),3)) return(_CGP);
  if(Equal(Var(0),4)) return(_CGM);
  if(Equal(Var(0),5)) return(MBOM);
  if(Equal(Var(0),6)) return(FLNT);
  if(Equal(Var(0),7)) return(FF4V);
  if(Equal(Var(0),8)) return(_AUS);
  if(Equal(Var(0),9)) return(JU58);
  if(Equal(Var(0),10)) return(JU59);
  if(Equal(Var(0),11)) return(SBOM);
  if(Equal(Var(0),12)) if(!Random(2)) return(KAC5); else return(Zufallsflint());
  if(Equal(Var(0),13)) return(HNTF);
  if(Equal(Var(0),14)) return(SHFT);
  if(Equal(Var(0),15)) return(SFLN);
  if(Equal(Var(0),16)) return(_SFN);
  if(Equal(Var(0),17)) return(FL58);
  if(Equal(Var(0),18)) return(J102);
  if(Equal(Var(0),19)) return(TFLN);
  if(Equal(Var(0),20)) if(!Random(3)) return(EFLN); else return(Zufallsflint());
  if(Equal(Var(0),21)) return(_RND);
return(0);

Zufallsflint2:
  if(!Random(120))
    return(VERN);
  SetVar(0,Random(11));
  if(Equal(Var(0),0)) if(!Random(4)) return(ATOM); else return(Zufallsflint2());
  if(Equal(Var(0),1)) return(CHS2);
  if(Equal(Var(0),2)) return(MSFL);
  if(Equal(Var(0),3)) return(KREI);
  if(Equal(Var(0),4)) return(SHF3);
  if(Equal(Var(0),5)) return(P57M);
  if(Equal(Var(0),6)) return(_MFF);
  if(Equal(Var(0),7)) return(SLGR);
  if(Equal(Var(0),8)) return(SHF2);
  if(Equal(Var(0),9)) return(MSHF);
  if(Equal(Var(0),10)) return(ZBOM);
return(0);

MakeGodMenu:
  Var(0) = Par(0);
  Var(1) = Par(1);
  AddMenuItem("Landschaft wiederherstellen","StartEvent",REEH,Var(0),0,-1,0,128,0,Var(1));
  AddMenuItem("Kamikaze","StartEvent",KIK1,Var(0),0,0,0,128,0,Var(1));
  AddMenuItem("Moffs","StartEvent",MF5B,Var(0),0,1,0,128,0,Var(1));
  AddMenuItem("Barbaren","StartEvent",KI58,Var(0),0,2,0,128,0,Var(1));
  AddMenuItem("Statue","StartEvent",ASDF,Var(0),0,4,0,128,0,Var(1));
  AddMenuItem("Gigantischer Kamikaze","StartEvent",BIG1,Var(0),0,5,0,128,0,Var(1));
  AddMenuItem("Winzige Kamikaze","StartEvent",WIG1,Var(0),0,6,0,128,0,Var(1));
  AddMenuItem("Bombenhagel","StartEvent",_WSP,Var(0),0,7,0,128,0,Var(1));
  AddMenuItem("Rambos","StartEvent",C158,Var(0),0,8,0,128,0,Var(1));
  AddMenuItem("Pfeil und Bogen Gegner","StartEvent",KB3A,Var(0),0,9,0,128,0,Var(1));
  AddMenuItem("Monsterregen","StartEvent",MONS,Var(0),0,10,0,128,0,Var(1));
  AddMenuItem("Apokalypse","StartEvent",NEBB,Var(0),0,11,0,128,0,Var(1));
  AddMenuItem("Flummiland","StartEvent",JU58,Var(0),0,12,0,128,0,Var(1));
  AddMenuItem("Halluzinationen","StartEvent",HNTF,Var(0),0,13,0,128,0,Var(1));
  AddMenuItem("Fallen","StartEvent",FA_3,Var(0),0,14,0,128,0,Var(1));
  AddMenuItem("Napalm","StartEvent",DFL2,Var(0),0,15,0,128,0,Var(1));
  AddMenuItem("Betonesel","StartEvent",ESEL,Var(0),0,16,0,128,0,Var(1));
  AddMenuItem("Armageddon","StartEvent",_AMA,Var(0),0,17,0,128,0,Var(1));
  AddMenuItem("Shockwave","StartEvent",SJ3V,Var(0),0,18,0,128,0,Var(1));
  AddMenuItem("Gravitationsstoß","StartEvent",_GNS,Var(0),0,19,0,128,0,Var(1));
  AddMenuItem("Flintregen","StartEvent",_FTS,Var(0),0,20,0,128,0,Var(1));
  AddMenuItem("Schwarzes-Loch-Runde","StartEvent",SLGR,Var(0),0,22,0,128,0,Var(1));
  AddMenuItem("Bombeneinheit","StartEvent",SHFT,Var(0),0,24,0,128,0,Var(1));
  AddMenuItem("Riesen Bombe","StartEvent",BGBM,Var(0),0,25,0,128,0,Var(1));
  AddMenuItem("Riesen Seelenstein","StartEvent",RGSS,Var(0),0,26,0,128,0,Var(1));
  AddMenuItem("Riesen Schwarzer Seelenstein","StartEvent",RSSS,Var(0),0,27,0,128,0,Var(1));
  AddMenuItem("Schallwellen","StartEvent",SJ4V,Var(0),0,28,0,128,0,Var(1));
  AddMenuItem("Schwarze Löcher","StartEvent",_SLC,Var(0),0,29,0,128,0,Var(1));
  AddMenuItem("Bonus Runde","StartEvent",ST58,Var(0),0,30,0,128,0,Var(1));
  AddMenuItem("Equipment","StartEvent",_EQP,Var(0),0,31,0,128,0,Var(1));
  AddMenuItem("Pokemon Kampf","StartEvent",P57M,Var(0),0,32,0,128,0,Var(1));
  AddMenuItem("Ärzte Rufen","StartEvent",KREI,Var(0),0,34,0,128,0,Var(1));
  AddMenuItem("Schwere Infanterie","StartEvent",SWIR,Var(0),0,37,0,128,0,Var(1));
  AddMenuItem("Wololo","StartEvent",JU59,Var(0),0,39,0,128,0,Var(1));
  AddMenuItem("Platztausch","StartEvent",RMMG,Var(0),0,40,0,128,0,Var(1));
  AddMenuItem("Keine Grenzen","StartEvent",_NOB,Var(0),0,41,0,128,0,Var(1));
  return(1);
