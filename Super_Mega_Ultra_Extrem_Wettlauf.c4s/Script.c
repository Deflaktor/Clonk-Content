/*--- Skylands - Parcour ---*/

// Global(0): 
// Global(1): Alles Stopp oder nicht

#strict

Initialize:
  StopAll();
  SetClimate(50);
  return(1);

Script1:
  Sound("3210");
  Message("   3...");
  return(1);

Script15:
  Message("...2...");
  return(1);

Script9:
  Message("...1...");
  return(1);

Script13:
  Message("...0!!!");
  if(Var(0)=FindObject(STOP))
    RemoveObject(Var(0));
  ResumeAll();
  goto(0);
  return(ScriptGo());

/* Spielerinitialisierung */

protected InitializePlayer: 
  if(Global(Par(0)*2+2)==0&&Global(Par(0)*2+3)==0) {
    SetGlobal(Par(0)*2+2,20);
    SetGlobal(Par(0)*2+3,620);
  }

  if(FrameCounter()<10) {
    if(Par(0)==0) {
      ChangeDef(MEN1,GetCrew(0));
      ObjectCall(GetCrew(Par(0)),"Menu1");
    } else {
      Enter(GetCrew(0),GetCrew(Par(0)));
    }
  }
  return(JoinPlayer(Par()));

NeueRunde:
  StopAll();
  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i)) {
      SetGlobal(i*2+2,Par(0));
      SetGlobal(i*2+3,Par(1));
      ObjectCall(GetCrew(i),"Selbstmord");
      --j;
    }
  StopAll();
  ScriptGo(1);
  return(1);

StopAll:
  Global(1)=1;
  ObjectCall(FindObject(_GCR),"Stop");
  while(Var(0)=FindObject(CLNK,0,0,0,0,0,0,0,0,Var(0))) ObjectCall(Var(0),"Stop");
  while(Var(0)=FindObject(PM7K,0,0,0,0,0,0,0,0,Var(0))) SetComDir(COMD_None(), Var(0));
  while(Var(0)=FindObject(PN7K,0,0,0,0,0,0,0,0,Var(0))) SetComDir(COMD_None(), Var(0));
  while(Var(0)=FindObject(BIK1,0,0,0,0,0,0,0,0,Var(0))) SetComDir(COMD_None(), Var(0));
  while(Var(0)=FindObject(HORS,0,0,0,0,0,0,0,0,Var(0))) SetComDir(COMD_None(), Var(0));
  return(1);

ResumeAll:
  Global(1)=0;
  ObjectCall(FindObject(_GCR),"Resume");
  while(Var(0)=FindObject(CLNK,0,0,0,0,0,0,0,0,Var(0))) ObjectCall(Var(0),"Resume");
  return(1);

DontMove:
  return(Global(1));

EndlessTankAmmo:
  return(PP7K);

NoTankDeparture:
  return(SetR(0,Local(0,Par(0))));

/* Neubeitritt */

private JoinPlayer:
  var obj=GetCrew(Par());
  DoEnergy(100000,obj);
  DoBreath(100,obj);
  SetPosition(Global(Par(0)*2+2), Global(Par(0)*2+3), obj);
  ObjectSetAction(obj,"Walk");
  SetXDir(0,obj);
  SetYDir(0,obj);
  return(1);

public RelaunchPlayer:
  Var(0)=GetCrew(Par(0));

  SetPhysical("CanScale",0,2,Var());
  SetPhysical("CanHangle",0,2,Var());
  SetCursor(Par(),Var());
  //Log(RndRelaunchMsg(), GetPlayerName(Par()));
  return(JoinPlayer(Par()));

private RndRelaunchMsg:
  if (!(Var()=Random(11))) return("%s hat versagt.");
  if (!--Var())            return("Netter Versuch, %s!");
  if (!--Var())            return("%s versucht es nochmal.");
  if (!--Var())            return("t0l, %s");
  if (!--Var())            return("Der Weg des %s endet hier.");
  if (!--Var())            return("Ein rejoin für %s");
  if (!--Var())            return("Genialer Abgang von %s");
  if (!--Var())            return("%s könnte Stuntman werden.");
  if (!--Var())            return("%s erforscht das Tiefland.");
  if (!--Var())            return("%s ist platt.");
                           return("%s verdient ein Denkmal.");