/*-- Battle Planet --*/

#strict

HazardLogs: return(1);

Initialize:
  ScriptGo(1);
  return(1);

Script30:
  // Neue Dronen erzeugen
  if (ObjectCount(_DRN)>10) 
    return(goto(1));
  CreateContents(_DRN,FindObject(_GTX,1200,500,250,250));
  CreateContents(_DRN,FindObject(_GTX,2153,325,50,50));
  return(goto(1));
 
InitializePlayer:
  DeployPlayer(Par(0));
 return(1);

DeployPlayer:
  // Sound
 Sound("PlayerJoin");
  //Luftabwurf erstes Mannschaftsmitglied
  ForcePosition( GetCrew(Par(0)), Sum(Random(Sum(LandscapeWidth(),-40)),+20), -20 );
 return(1);  
 
RelaunchPlayer:
  // Par(0) ist kein gültiger Spieler
  if (Not(GetPlayerName(Par(0)))) return (0);
  // Neues Mannschaftsmitglied erschaffen
  MakeCrewMember(CreateObject(HZCK,50,-50,Par(0)),Par(0));
  SetCursor(Par(0),GetCrew(Par(0)));
  // Punktverlust
  DoScore(Par(0),-300);
  // Meldung
  Log("Neuer Einsatz: %s",GetPlayerName(Par(0)));
  // Neustarten
  DeployPlayer(Par(0));
 return(1);

MainEnergySupply:
  return(SEqual(GetAction(FindObject(_GEN)),"Running"));