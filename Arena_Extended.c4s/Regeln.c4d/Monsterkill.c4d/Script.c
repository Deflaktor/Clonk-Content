/*-- Monsterjagd --*/

#strict

local currentGod, framecounter, norespawn, musiclevel, godmodecost;

Initialize:
  SetPosition(25,25);
  SetAction("Check");
  return(1);

GetGodModeCost:
  return(godmodecost);
  
Check:
  if(!godmodecost) {
    godmodecost = 100*(ObjectCount(GetID())+1);
    while(Var(0)=FindObject(GetID(),0,0,0,0,0,0,0,0,Var(0))) RemoveObject(Var(0));
  }
  if(!currentGod)
    return(0);
  DeleteCreateEnemies();
  var plr = GetOwner(currentGod);
  // Still alive and well?
  if(!(currentGod->IsGodMode()))
    return(GodModeDeactivated());
  // Increase Timer
  if(IncreaseTime()) {
    // God Mode Swap every two minutes
    if(Local(plr)>0&&(Local(plr)==30||Local(plr)%121==0)) {
      GameCall("Event40");
    }
    if(Local(plr)==60)
      PlayRightMusic();
    if(Local(plr)<=30)
      Sound("BIP2.wav", 1);
    else
      Sound("Clock.wav", 1);
  }
  // Check Fulfilled
  if(Fulfilled()) {
    norespawn = 1;
    // Make player epic
    GetCrew(plr)->SetEpicMode();
  }
  // Any players alive?
  if(norespawn) {
    var i = GetPlayerCount();
    var alive = false;
    while (i--) {
      if (GetPlayerName(i)) {
        if(i != plr) {
          if(GetHiRank(i))
            alive = true;
        }
      }
    }
    // Nobody alive? -> End Game
    if(!alive)
      RewardPlayerAndEndGame(plr);
  }
  return(1);
  
IncreaseTime:
  if(norespawn)
    return(0);
  framecounter++;
  if(framecounter < 35/5)
    return(0);
  framecounter = 0;
  var plr = GetOwner(currentGod);
  Local(plr)--;
  if(CalcSec(Local(plr))<10)
    Message(Format("Sieges-Countdown %d:0%d", CalcMin(Local(plr)), CalcSec(Local(plr))),currentGod);
  else
    Message(Format("Sieges-Countdown %d:%d", CalcMin(Local(plr)), CalcSec(Local(plr))),currentGod);
  return(1);
  
RewardPlayerAndEndGame:
  SetAction("Wait4End");
  MusicLevel(0);
  Sound("Applause", 1);
  framecounter = 0;
  return(1);
  
RoundOverCheck:
  var plr = GetOwner(currentGod);
  Message(Format("%s gewinnt die Runde! Glückwunsch!", GetPlayerName(plr)));
  framecounter++;
  MusicLevel(framecounter*4);
  if(framecounter<5*35/5)
    return(0);
  DoCrewExp(1000, GetCursor(plr));
  GameOver();
  SetAction("Idle");
  return(1);
  
Fulfilled:
  var plr = GetOwner(currentGod);
  if(Local(plr) == 0) {
    Local(plr) = -1;
    PlayRightMusic();
  }
  if(Local(plr) <= 0) {
    Local(plr) = -1;
    return(1);
  }
  return(0);

CalcMin:
  return(Par(0) / 60);
  
CalcSec:
  return(Par(0) % 60);

GodModeDeactivated:
  if(Par(0))
    if(currentGod!=Par(0))
      return(0);
  currentGod = 0;
  PlayRightMusic();
  return(1);

GodModeActivated:
  if(!Par(0))
    return(0);
  currentGod = Par(0);
  var plr = GetOwner(Par(0));
  // 6 (Minuten) * 60 (Sekunden)
  // swapTime = 30;
  if(!Local(plr))
    SetLocal(plr, 6*60);
  PlayRightMusic();
  return(1);

PlayRightMusic:
  var plr = GetOwner(currentGod);
  if(currentGod) {
    if(Local(plr)<=-1) {
      SetPlayList("*@luf2savior.mid");
      Music("@luf2savior.mid", 1);
    } else if(Local(plr)<=60) {
      SetPlayList("*@Cornered.mid");
      Music("@Cornered.mid", 1);
    } else {
      SetPlayList("*@Komplizierte Sache.mid");
      Music("@Komplizierte Sache.mid", 1);
    }
  } else {
    SetPlayList("*1.mid");
    Music("1.mid", 1);
  }
  MusicLevel(100-GameCall("MusicVolume"));
  return(1);
  
GetCurrentGod:
  return(currentGod);
  
GetNoRespawn:
  return(norespawn);
  
DeleteCreateEnemies:
  if(norespawn)
    return(1);
  var plr = GetOwner(currentGod);
  if(!Random(50))
    Kill(FindObject(KIK1,0,0,0,0,0,"Walk"));
  if(!Random(100))
    Kill(FindObject(DIL1,0,0,0,0,0,"Walk"));
  if(!Random(100))
    Kill(FindObject(KIL1,0,0,0,0,0,"Walk"));
    
  if(!Random(Max(Local(plr)*5,50)))
    And(
        SetVar(0,CreateObject(GIK1,GetX(currentGod),0,-1)),
        SetXDir(Sub(25,Random(51)),Var(0)),
        SetYDir(Sum(20,Random(16)),Var(0))
       );
       
  if(Local(plr)<=60&&!Random(200)) {
    CreateObject(KB3A,Random(LandscapeWidth()),0,-1);
  }
  if(Local(plr)<=60&&!Random(200)) {
    CreateObject(KI58,Random(LandscapeWidth()),0,-1);
  }
  if(Local(plr)<=60&&!Random(200)) {
    CreateObject(FMNS,Random(LandscapeWidth()),0,-1);
  }
  if(Local(plr)<=60&&!Random(200)) {
    CreateObject(MONS,Random(LandscapeWidth()),0,-1);
  }
  if(Local(plr)<=60&&!Random(200)) {
    CreateObject(WIG1,Random(LandscapeWidth()),0,-1);
  }
  if(Local(plr)<=60&&!Random(200)) {
    CreateObject(C158,Random(LandscapeWidth()),0,-1);
  }
  return(1);
  
protected func Activate(iPlayer) {
  return(MessageWindow("Ein Spieler muss 1000 Gold sammeln um zum Gott zu werden.", iPlayer));
}

