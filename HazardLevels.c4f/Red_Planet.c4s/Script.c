/* -- Red Planet -- */

#strict

Initialize:
  ScriptGo(1);
  return(1);

Script60:
  // Neue Dronen erzeugen
  if (ObjectCount(_DRN)<5) {
    CreateContents(_DRN,FindObject(_GT1,0,0));
    CreateContents(_DRN,FindObject(_GTX,0,0));
  }
  return(goto(1));

RelaunchPlayer:
  // Par(0) ist kein gültiger Spieler
  if (Not(GetPlayerName(Par(0)))) return (0);
  // Neues Mannschaftsmitglied erschaffen
  MakeCrewMember(CreateObject(HZCK,50,-50,Par(0)),Par(0));
  SetCursor(Par(0),GetCrew(Par(0)));
  // Punktverlust
  DoScore(Par(0),-250);
  // Meldung
  Log("Neuer Einsatz: %s",GetPlayerName(Par(0)));
  // Neustarten
  DeployPlayer(Par(0));
  return(1);

InitializePlayer:
  DeployPlayer(Par(0));
  return(1);

DeployPlayer:
  // Sound
  Sound("PlayerJoin");

  // Shuttle erzeugen
    SetVar(0,CreateObject(SHT1,Sum(Random(Sum(LandscapeWidth(),-200)),+100),-50,Par(0)));
  // Shuttle konfigurieren
  ObjectCall(Var(0),"DisablePlayerControl");
  ObjectCall(Var(0),"SetHomebaseAutomatic",1);

  // Alte Sender zerstören
  while ( SetVar(9,FindObject(_WP4,0,0,0,0,0,0,0,0,Var(9))) )
    if (Equal(GetOwner(Var(9)),Par(0)))
      RemoveObject(Var(9));
  // Sender für erstes Mannschaftsmitglied erzeugen
  CreateContents( _WP4, GetCrew(Par(0)) );

  // Wenn Shuttle im Orbit, Mannschaft per Shuttle absetzen
  if (LessThan(GetY(Var(0)),-30))
    return( ShuttleCrewDispatch(Var(0),GetCrew(Par(0))) );

  // Sonst Luftabwurf erstes Mannschaftsmitglied
  ForcePosition( GetCrew(Par(0)), Sum(Random(Sum(LandscapeWidth(),-40)),+20), -20 );

  return(1);  
  
ShuttleCrewDispatch:
  // Mannschaft ins Shuttle
  Enter( Par(0), Par(1) );
  // Landekommando
  ForcePosition(Var(0),Sum(Random(Sum(LandscapeWidth(),-200)),+100),-50);
  SetDir(DIR_Right(),Var(0));
  SetCommand( Par(0), "MoveTo", 0, Sum(GetX(Par(0)),300), 1600 );
  return(1);

MainEnergySupply:
  return(GetAction(FindObject(_GEN))S="Running");
