/* -- Forschungsstation -- */

#strict

static respawnSettings, droneDelay;

SetDeployPlayerIfHeDiesInSky:
  respawnSettings = respawnSettings | 1;
  return(respawnSettings);
  
ResetDeployPlayerIfHeDiesInSky:
  respawnSettings = respawnSettings & ~1;
  return(respawnSettings);
  
SpawnPlayerAtRandomRespawn:
  respawnSettings = respawnSettings | 2;
  return(respawnSettings);

SpawnPlayerAtNearestRespawn:
  respawnSettings = respawnSettings & ~2;
  return(respawnSettings);

IsDeployPlayerIfHeDiesInSky:
  return(respawnSettings & 1);  
  
IsSpawnPlayerAtRandomRespawn:
  return(respawnSettings & 2);

HazardLogs: return(1);

NoHotlaser:
  return(1);

ShowCustomSpawns:
  while(Var(0)=FindObject(Par(0),0,0,0,0,0,0,0,0,Var(0)))
    Message(Par(1),Var(0));
  return(1);

CreateOzarkInEveryCrate:
  while(Var(0)=FindObject(_CRT,0,0,0,0,0,0,0,NoContainer(),Var(0)))
    if(!GBackSolid(GetX(Var(0)), GetY(Var(0)) -20)&&!GBackSolid(GetX(Var(0)), GetY(Var(0)) -30))
    CreateContents(OZRK,Var(0));
  return(1);
  
SetCustomSpawns:
  while(Var(0)=FindObject(Par(0),0,0,0,0,0,0,0,0,Var(0)))
    Var(0)->Initialize();
  return(1);

Initialize:
  MusicLevel(50);
  SetGlobal(9764,0);
  SetGlobal(6,1);
  SetGlobal(5,20000);
  ScriptGo(1);
  while(Var(0)=FindObject(AIRL,0,0,0,0,0,0,0,0,Var(0))) {
    Var(0)->Pumping();
    SetLocal(0,0,Var(0));
  }
  //Var(0)=CreateObject(TM1_);
  //Var(0)->SetMusic("@M3intro",true);
  //Var(0)->Execute();
 // RemoveObject(Var(0));
  return(1);

MaxPhasorPower:
  if(Global(6)) return(10);
  return(0);
  
  
DestructableLandscape:
  return(0);

MedkitHeal:
  if(Global(6))
    return(50);
  return(0);

EndlessRegenerate:
  if(Global(6))
    return(1);
  return(0);

Script1:
  ObjectCall(CreateObject(MEN1,0,0,-1),"Menu1");
  return(goto(2));

Script2:
  if (FindObject(MEN1)) goto(2);
  ScriptGo(1);
  return(1);

Script3:
var i;
for(i=0;i<(Global(3)+1)*10;i++)
  CreateAlien(ST5B);
for(i=0;i<(Global(3)+1)*10;i++)
  CreateAlien(_CHP);
SetGlobal(9764,1);
var i;
for(i=0;i<GetPlayerCount();i++)
{
RemoveObject(GetCursor(i));
LaunchPlayer(i);
}
ScriptGo(1);
return(1);

Script33:
  // Neue Dronen erzeugen alle 3*3 Sekunden
  droneDelay++;
  if (MainEnergySupply()&&droneDelay>3) 
    if (LessThan(ObjectCount(_DRN),3)) {
    CreateContents(_DRN,FindObject(_GT1,1500,600,100,100));
    droneDelay=0;
  }
  if (ObjectCount(SCG2)<1&&Global(33)) CreateContents(SCG2,FindObject(_GT1,1500,600,100,100));
  if (ObjectCount(GB02)<1&&Global(33)) CreateContents(GB02,FindObject(BX3V,1300,1800,200,200));
  if (ObjectCount(GB01)<1&&!Global(33)) CreateContents(GB01,FindObject(BX3V,1300,1800,200,200));
  // Shuttles im Orbit: Wertgegenstände verkaufen
  SetVar(0,-1);
  while (LessThan(SetVar(0,Sum(Var(0),+1)),12))
    if (SetVar(1,FindPlayerShuttle(Var(0))))
      if (LessThan(GetY(Var(1)),-30))
        SellValuableContents(Var(1),GetOwner(Var(1)));
  // Neue Chipies erzeugen
  if(!Global(648)&&!Global(6))
    if(ObjectCount(_CHP,790,1050,140,70)<4)
      SetLocal(0,2,CreateObject(_CHP,850,1085,-1));
  // Fireballs erzeugen (Wenn nicht story-modus)
  if(!Global(6)&&ObjectCount(_FBL)<10) {
    CreateAlien(_FBL);
  }
  CreateFireballInRoom();
  return(goto(4));
  
Script13:
  return(CreateFireballInRoom()); 
Script18:
  return(CreateFireballInRoom());
Script23:
  return(CreateFireballInRoom());
Script28:
  return(CreateFireballInRoom());
  
CreateFireballInRoom:
  if (Global(6) && ObjectCount(_FBL,2800,1525,3060-2800,1660-1525) < 30) {
    CreateObject(_FBL,2840+Random(3030-2840),1560+Random(1630-1560),-1);
  }
  return(1);

InitializePlayer:
  // Mit allen Spielern verfeinden
  var i,j;
  for (j = GetPlayerCount(); j > 1; i++) 
    if (GetPlayerName(i) && (i != Par(0)))
    {
      SetHostility(i, Par(0), 1, 1);
      SetHostility(Par(0), i, 1, 1);
      --j;
    }
  if(Not(Global(9764)))
    And(SetPosition(Random(LandscapeWidth()),0,GetHiRank(Par(0))),return(1));
  RemoveObject(GetHiRank(Par(0)));
  LaunchPlayer(Par(0));
  return(2);

RelaunchBot:
  if(Global(6))
    return(1);
  Var(0)=CreateObject(HK00,50,-50,-1);
  while(true) {
    var x,y;
    x = 20 + Random(LandscapeWidth()-20);
    y = 20 + Random(LandscapeHeight()/2-20);
    if(GetMaterial(x,y)==Material("Wall")) {
      SetPosition(x, y, Var(0));
      break;
    }
  }
  return(1);
  
CreateShuttle:
  // Shuttle erzeugen
  if (Not(SetVar(0,FindPlayerShuttle(Par(0)))))
    SetVar(0,CreateObject(SHT1,Sum(Random(Sum(LandscapeWidth(),-200)),+100),-50,Par(0)));
  // Shuttle konfigurieren
  ObjectCall(Var(0),"DisablePlayerControl");
  ObjectCall(Var(0),"SetHomebaseAutomatic",1);
  return(Var(0));

DeployPlayer:

  // Sound
  Sound("PlayerJoin");

  var clk=GetCrew(Par(0));
  
  // Alte Schallpistole zerstören
  while ( SetVar(9,FindObject(_WP4,0,0,0,0,0,0,0,0,Var(9))) )
    if (Equal(GetOwner(Var(9)),Par(0)))
      RemoveObject(Var(9));
  // Schallpistole für erstes Mannschaftsmitglied erzeugen
  CreateContents( _WP4, clk );

  // Wie viele Respawn Points gibt es auf der Map?
  var respawnPoints=0;
  while(Var(1)=FindObject(0,0,0,0,0,0,0,0,0,Var(1)) )
  if(ObjectCall(Var(1),"IsRespawnPoint"))
    if(!ObjectCall(Var(1),"GetTarget"))
      respawnPoints++;
  Var(1)=0;
    
  if(respawnPoints==0||(IsDeployPlayerIfHeDiesInSky()&&GBackSky(GetX(clk),GetY(clk)-10))) {
      if(IsDeployPlayerIfHeDiesInSky()&&GBackSky(GetX(clk),GetY(clk)-10))
      Var(1)=1;
    // Shuttle erzeugen
    Var(0)=CreateShuttle(Par(0));

    // Wenn Shuttle im Orbit, Mannschaft per Shuttle absetzen
    if (LessThan(GetY(Var(0)),-30))
    return( ShuttleCrewDispatch(Var(0),clk,Var(1)) );

    // Sonst Luftabwurf erstes Mannschaftsmitglied
    SetPosition( Random(LandscapeWidth()-40)+20, -20, clk );
  } else if(IsSpawnPlayerAtRandomRespawn()) {
  // Suche einen zufälligen aus.
  var respawnPointIndex=Random(respawnPoints);
  if(respawnPoints)
  while(Var(1)=FindObject(0,0,0,0,0,0,0,0,0,Var(1)) )
    if(ObjectCall(Var(1),"IsRespawnPoint"))
        if(!ObjectCall(Var(1),"GetTarget")) {
      if(respawnPointIndex==0)
        return(SetPosition( GetX(Var(1)),GetY(Var(1)),clk ));  
      respawnPointIndex--;
      }
  } else {
    // Nahester Respawn Point
    while(Var(1)=clk->FindObject(0,0,0,-1,-1,0,0,0,0,Var(1)) )
    if(ObjectCall(Var(1),"IsRespawnPoint")) {
      if(Var(2)=Var(1)->GetTarget())
      return(SetPosition( GetX(Var(2)),GetY(Var(2)),clk ));
      else
      return(SetPosition( GetX(Var(1)),GetY(Var(1)),clk ));
    }
  }
  return(1);
  
ShuttleCrewDispatch:
  // Mannschaft ins Shuttle
  Enter( Par(0), Par(1) );
  // Landekommando
  ForcePosition(Par(0),Sum(Random(Sum(LandscapeWidth(),-200)),+100),-50);
  SetDir(DIR_Right(),Par(0));
  if(Global(6)) {
    if(!Par(2))
      Par(1)->SetEnabled(0);
    ForcePosition(Par(0),2340,-50);
    SetCommand( Par(0), "MoveTo", 0, 2440, 200 );
    return(1);
  }
  SetCommand( Par(0), "MoveTo", 0, Sum(GetX(Par(0)),300), 1600 );
  return(1);

SellValuableContents: // Par(0) Objekt, Par(1) Spieler
  // Alle Datenwürfel, Mineralien und Materialien verkaufen
  while (SetVar(0,FindContents(_DC1,Par(0)))) SellHomebaseMaterial(Par(1),Var(0));
  while (SetVar(0,FindContents(_DC2,Par(0)))) SellHomebaseMaterial(Par(1),Var(0));
  while (SetVar(0,FindContents(_DC3,Par(0)))) SellHomebaseMaterial(Par(1),Var(0));

  // Verschachtelten Inhalt durchsuchen
  SetVar(0,-1);
  while (SetVar(1,Contents( SetVar(0,Sum(Var(0),+1)), Par(0) )))
    SellValuableContents(Var(1),Par(1));

  return(1);

BuyHomebaseMaterial: // Par(0) Spieler, Par(1) Objekt-ID, Par(2) Zielobjekt
  // Geld abziehen
  SetWealth( Par(0), Sub(GetWealth(Par(0)),Value(Par(1))) );
  Sound("UnCash");
  // Heimatbasismaterial abziehen
  DoHomebaseMaterial(Par(0),Par(1),-1);
  // Objekt in Zielobjekt erzeugen
  Enter(Par(2),CreateObject(Par(1),50,50,Par(0)));
  // Erfolg
  return(1);

SellHomebaseMaterial: // Par(0) Spieler, Par(1) Objekt
  // Geld anrechnen
  SetWealth( Par(0), Sum(GetWealth(Par(0)),GetValue(Par(1))) );
  Sound("Cash");
  // Heimatbasismaterial addieren
  DoHomebaseMaterial(Par(0),GetID(Par(1)),+1);
  // Objekt entfernen
  RemoveObject(Par(1));
  // Erfolg
  return(1);  

LaunchPlayer:
  // Par(0) ist kein gültiger Spieler
  if (Not(GetPlayerName(Par(0)))) return (0);
  // Abfrage Wie viele Leben
  if (!Global(14)) {
    if (Global(Par(0)+10)<1) return(Log("%s hat keine Leben mehr übrig.",GetPlayerName(Par(0))));
    SetGlobal(Par(0)+10,Global(Par(0)+10)-1);
    MakeCrewMember(SetVar(0,CreateObject(HZCK,50,-50,Par(0))),Par(0));
    ResetPhysical(Var(0));
    DoEnergy(1000,Var(0));
    SetCursor(Par(0),GetCrew(Par(0)));
    DoScore(Par(0),-250);
    Log("%s hat noch %d Leben übrig.",GetPlayerName(Par(0)),Global(Par(0)+10));
    DeployPlayer(Par(0));
    return(1);
  }
  // Neues Mannschaftsmitglied erschaffen
  MakeCrewMember(SetVar(0,CreateObject(HZCK,50,-50,Par(0))),Par(0));
  ResetPhysical(Var(0));
  DoEnergy(1000,Var(0));
  SetCursor(Par(0),GetCrew(Par(0)));
  // Punktverlust
  DoScore(Par(0),-250);
  // Meldung
  Log("Neuer Einsatz: %s",GetPlayerName(Par(0)));
  // Neustarten
  DeployPlayer(Par(0));
  return(1);

FindPlayerShuttle:
  while (SetVar(0,FindObject(SHT1,0,0,0,0,0,0,0,0,Var(0))))
    if (Equal(GetOwner(Var(0)),Par(0)))
      return(Var(0));
  return(0);
 
MainEnergySupply:
  var generator = FindObject(_GEN);
  if(Global(6)) {
    if(GetID(Par(0))==_LFP||GetID(Par(0))==_LFS||GetID(Par(0))==AIRL)
      if(Local(1,generator)||Local(2,generator)||Local(3,generator))
        return(0);
  if(GetID(Par(0))==_HS3) return(1);
}
  return(SEqual(GetAction(generator),"Running"));

Gewonnen:
  return(CreateObject(_BA9));
