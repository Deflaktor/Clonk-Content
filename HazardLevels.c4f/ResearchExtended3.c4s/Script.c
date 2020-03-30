
/* -- Forschungsstation -- */

#strict

HazardLogs: return(1);

Initialize:
  CreateObject(_YB0,2145, 825, -1);
  ScriptGo(1);
  return(1);

AlleSpwInit:
  while(Var(0)=FindObject(_SPW,0,0,0,0,0,0,0,0,Var(0)))
    Var(0)->EnterIt();
  return(1);
Script30:
  // Neue Dronen erzeugen
  if (LessThan(ObjectCount(_DRN),5)) CreateContents(_DRN,FindObject(_GT1,1000,500,250,250));
  // Shuttles im Orbit: Wertgegenstände verkaufen
  SetVar(0,-1);
  while (LessThan(SetVar(0,Sum(Var(0),+1)),12))
    if (SetVar(1,FindPlayerShuttle(Var(0))))
      if (LessThan(GetY(Var(1)),-30))
        SellValuableContents(Var(1),GetOwner(Var(1)));
  return(goto(1));

InitializePlayer:
  DeployPlayer(Par(0));
  return(1);

DeployPlayer:

  // Sound
  Sound("PlayerJoin");

  // Shuttle erzeugen
  if (Not(SetVar(0,FindPlayerShuttle(Par(0)))))
    SetVar(0,CreateObject(SHT1,Sum(Random(Sum(LandscapeWidth(),-200)),+100),-50,Par(0)));
  // Shuttle konfigurieren
  ObjectCall(Var(0),"DisablePlayerControl");
  ObjectCall(Var(0),"SetHomebaseAutomatic",1);

  // Alte Sender zerstören
  while ( SetVar(9,FindObject(_RDO,0,0,0,0,0,0,0,0,Var(9))) )
    if (Equal(GetOwner(Var(9)),Par(0)))
      RemoveObject(Var(9));
  // Sender für erstes Mannschaftsmitglied erzeugen
  CreateContents( _RDO, GetCrew(Par(0)) );

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

FindPlayerShuttle:
  while (SetVar(0,FindObject(SHT1,0,0,0,0,0,0,0,0,Var(0))))
    if (Equal(GetOwner(Var(0)),Par(0)))
      return(Var(0));
  return(0);
 
MainEnergySupply:
  return(SEqual(GetAction(FindObject(_GEN)),"Running"));


