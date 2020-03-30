
/* -- PlanetXtreme -- */

#strict

HazardLogs: return(1);

CreateAlien:
  return(PlaceInMaterial(Par(0),Material("Wall"),100000));

DestructableLandscape:
  return(1);
  
StartingScore:
  var score;
  score = 0;
  score += GetValue(0,SHT1); // Raumfähre
  score += GetValue(0,HZCK); // Hazardclonk
  score += GetValue(0,_WP4); // Schallpistole
  return(score);

/*-- Szenario beginnt --*/
Initialize:
  SetGlobal(0,2);
  SetGlobal(4,0);
  SetGlobal(5,100);
  SetGlobal(648,1);
  AddRandomItems();
  ScriptGo(1);
  ResetAlienPhysicals();
  return(0);

ResetAlienPhysicals:
  while(Var(0)=FindObject(0,0,0,0,0,0,0,0,0,Var(0)))
    ObjectCall(Var(0),"Refit");
  return(1);

AddRandomItems:
  var id, sp, door;
  var uebrig;
  Var(0) = CreateObject(_RI_);
  Var(0)->Add(_WP1);
  Var(0)->AddAllExceptDatacubesAndWeapons();
 /* for(var i=1;i<=5;i++) {
    door = FindRandomEmptyDoor(door);
    sp = CreateObject(_SPW, GetX(door), GetY(door));
    SetLocal(0, Var(0)->Get(), sp);
    SetLocal(1, CreateContents(Local(0), door), sp);
    SetLocal(3, door, sp);
    ObjectSetAction(sp, "Set");
  }
*/
  while(door = FindRandomEmptyDoor(door)) {
    if(Random(4)) {
      CreateContents(Var(0)->Get(), door);
      /*
      sp = CreateObject(_SPW, GetX(door), GetY(door));
      SetLocal(0, Var(0)->Get(), sp);
      SetLocal(1, CreateContents(Local(0), door), sp);
      SetLocal(3, door, sp);
      ObjectSetAction(sp, "Set");*/
    } else {
      uebrig++;
    }
  }
  RemoveObject(Var(0));
  return(uebrig);

FindRandomEmptyDoor:
  Var(0) = Par(0);
  while(Var(0) = FindObject(0,0,0,0,0,0,0,0,NoContainer(),Var(0)))
    if(!Contents(0,Var(0)))
      if(Compartment(Var(0)))
        return(Var(0));
  return(0);

Compartment:
  if(GetID(Par(0))==_CM1)
    return(1);
  if(GetID(Par(0))==_RM1)
    return(1);
  if(GetID(Par(0))==_CRT)
    return(1);
  if(GetID(Par(0))==BX3V)
    return(1);
  if(GetID(Par(0))==_LCK)
    return(1);
  if(GetID(Par(0))==_CR2)
    return(1);
  if(GetID(Par(0))==LORY)
    return(1);
  return(0);

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

  // Alte Schallpistole zerstören
  while ( SetVar(9,FindObject(_WP4,0,0,0,0,0,0,0,0,Var(9))) )
    if (Equal(GetOwner(Var(9)),Par(0)))
      RemoveObject(Var(9));
  // Schallpistole für erstes Mannschaftsmitglied erzeugen
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

RelaunchKi:
  return(1);

FindPlayerShuttle:
  while (SetVar(0,FindObject(SHT1,0,0,0,0,0,0,0,0,Var(0))))
    if (Equal(GetOwner(Var(0)),Par(0)))
      return(Var(0));
  return(0);
 
MainEnergySupply:
  var dist, obj;
  dist = 999999;
  while(SetVar(0,FindObject(_GEN,0,0,0,0,0,0,0,0,Var(0))))
    if(SetVar(1,ObjectDistance(Var(0),Par(0)))<dist) {
      obj = Var(0);
      dist = Var(1);
    }
  return(SEqual(GetAction(obj),"Running"));

Script120:
  if(FrameCounter()>=100000) {
      Var(0)=FindObject(WAY1);
      SetLocal(0,1,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
      Var(0)=FindObject(WAY2);
      SetLocal(0,2,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
      Var(0)=FindObject(WAY3);
      SetLocal(0,3,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
      Var(0)=FindObject(WAY4);
      SetLocal(0,4,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
      Var(0)=FindObject(WAY5);
      SetLocal(0,5,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
      Var(0)=FindObject(WAY6);
      SetLocal(0,6,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
      Var(0)=FindObject(WAY7);
      SetLocal(0,7,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
      Var(0)=FindObject(WAY8);
      SetLocal(0,8,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
      Var(0)=FindObject(WAY9);
      SetLocal(0,0,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
      CreateContents(_DRN,FindObject(_GTX));
    return(1);
  }
  // Neue Dronen erzeugen
  if (LessThan(ObjectCount(_DRN),4)) CreateContents(_DRN,FindObject(_GTX));
  return(goto(1));

Script130:
  Var(0)=FindObject(WAY1);
  SetLocal(0,1,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
  Var(0)=FindObject(WAY2);
  SetLocal(0,2,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
  Var(0)=FindObject(WAY3);
  SetLocal(0,3,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
  Var(0)=FindObject(WAY4);
  SetLocal(0,4,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
  Var(0)=FindObject(WAY5);
  SetLocal(0,5,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
  Var(0)=FindObject(WAY6);
  SetLocal(0,6,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
  Var(0)=FindObject(WAY7);
  SetLocal(0,7,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
  Var(0)=FindObject(WAY8);
  SetLocal(0,8,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
  Var(0)=FindObject(WAY9);
  SetLocal(0,0,CreateObject(_DRN,GetX(Var(0)), GetY(Var(0))));
  CreateContents(_DRN,FindObject(_GTX));
  return(1);

Script140:
  return(Script130());

Script160:
  return(Script130());

Script180:
  return(Script130());

Script200:
  return(Script130());

Script320:
  // Neue Dronen erzeugen
  if (LessThan(ObjectCount(_DRN),4)) CreateContents(_DRN,FindObject(_GTX));
  return(goto(201));