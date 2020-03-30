
#strict

InitializePlayer:
  Sound("PlayerJoin");
  SetVar(0,Par(0));
  if(Equal(Var(0),0)) ForcePosition(GetCrew(Par(0)),GetX(FindObject(_PS1)),GetY(FindObject(_PS1)));
  if(Equal(Var(0),1)) ForcePosition(GetCrew(Par(0)),GetX(FindObject(_PS2)),GetY(FindObject(_PS2)));
  if(Equal(Var(0),2)) ForcePosition(GetCrew(Par(0)),GetX(FindObject(_PS3)),GetY(FindObject(_PS3)));
  if(Equal(Var(0),3)) ForcePosition(GetCrew(Par(0)),GetX(FindObject(_PS4)),GetY(FindObject(_PS4)));
  if(Equal(Var(0),4)) ForcePosition(GetCrew(Par(0)),GetX(FindObject(_PS5)),GetY(FindObject(_PS5)));
  if(Equal(Var(0),5)) ForcePosition(GetCrew(Par(0)),GetX(FindObject(_PS6)),GetY(FindObject(_PS6)));
  if(Equal(Var(0),6)) ForcePosition(GetCrew(Par(0)),GetX(FindObject(_PS7)),GetY(FindObject(_PS7)));
  if(Equal(Var(0),7)) ForcePosition(GetCrew(Par(0)),GetX(FindObject(_PS8)),GetY(FindObject(_PS8)));  
  return(1);  
  
Initialize:
  ScriptGo(1);
  return(1);
  
Script5:
  RelaunchBot();
  ScriptGo(0);
  return(1);
  
RelaunchBot:
  Var(0)=CreateObject(HK00,50,-50,-1);
  DeployPlayer(Var(0));
  return(1);
  
RelaunchPlayer:
   // Par(0) ist kein gültiger Spieler
   if (Not(GetPlayerName(Par(0)))) return (0);
   // Neues Mannschaftsmitglied erschaffen
   Var(0)=CreateObject(HZCK,50,-50,Par(0));
   MakeCrewMember(Var(0),Par(0));
   SetCursor(Par(0),Var(0));
   // Punktverlust
   DoScore(Par(0),-250);
   // Meldung
   Log("%d Ticks: %s benoetigt schon wieder Nachschub.",Local(0,FindObject(_UHR)),GetPlayerName(Par(0)));
   // Neustarten
   DeployPlayer(Var(0));
   return(1);

DeployPlayer:
  Sound("PlayerJoin");
  SetVar(0,Par(0));
  SetVar(1,Random(8));
  if(Equal(Var(1),0)) ForcePosition(Var(0),GetX(FindObject(_PS1)),GetY(FindObject(_PS1)));
  if(Equal(Var(1),1)) ForcePosition(Var(0),GetX(FindObject(_PS2)),GetY(FindObject(_PS2)));
  if(Equal(Var(1),2)) ForcePosition(Var(0),GetX(FindObject(_PS3)),GetY(FindObject(_PS3)));
  if(Equal(Var(1),3)) ForcePosition(Var(0),GetX(FindObject(_PS4)),GetY(FindObject(_PS4)));
  if(Equal(Var(1),4)) ForcePosition(Var(0),GetX(FindObject(_PS5)),GetY(FindObject(_PS5)));
  if(Equal(Var(1),5)) ForcePosition(Var(0),GetX(FindObject(_PS6)),GetY(FindObject(_PS6)));
  if(Equal(Var(1),6)) ForcePosition(Var(0),GetX(FindObject(_PS7)),GetY(FindObject(_PS7)));
  if(Equal(Var(1),7)) ForcePosition(Var(0),GetX(FindObject(_PS8)),GetY(FindObject(_PS8)));
  return(1);
  
MainEnergySupply:
  return(1);