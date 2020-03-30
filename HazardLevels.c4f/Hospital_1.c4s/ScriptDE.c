/* -- Krankenstation -- */

// Global 0: Energie

HazardLogs: return(1);
MinReinforcementsScore: return(520);

Initialize:
  SetGlobal(0,30);
  ScriptGo(1);
  return(1);

RelaunchPlayer:
  // Par(0) ist kein gültiger Spieler
  if (Not(GetPlayerName(Par(0)))) return (0);
  // Neues Mannschaftsmitglied erschaffen
  MakeCrewMember(SetVar(1,CreateObject(HZCK,Random(LandscapeWidth()),-50,Par(0)),Par(0)));
  SetCursor(Par(0),Var(1));
  // Volle Energie
  DoEnergy(+100,Var(1));
  // leichter Punktverlustd
  DoScore(Par(0),-25);
  // Alte Sender zerstören
  while(SetVar(9,FindObject(_RDO,0,0,0,0,0,0,0,0,Var(9))))
    if(Equal(GetOwner(Var(9)),Par(0)))
      ObjectCall(Var(9),"SelfDestruct");
  // neuer Sender
  SetOwner(Par(0),CreateContents(_RDO,Var(1)));
  // Meldung
  Log("Neuer Einsatz: %s",GetPlayerName(Par(0)));
  // Drone erstellen
  SetVar(0,CreateObject(_GDR,0,0));
  SetPosition(GetX(Var(1)),GetY(Var(1)),Var(0));
  // Dronen auf Clonk ausrichten
  SetLocal(0,Var(1),Var(0));
  // Andersrum
  SetLocal(0,Var(0),Var(1));
  // Sound
  Sound("PlayerJoin");
  return(1);

Script30:
  //keine Monster mehr da?    
  if(And(Not(FindObject(_ICH)),Not(FindObject(OZRK)))
    Resume();
  DoGlobalEnergy(-5);
  if(LessThan(GetGlobalEnergy(),0))
    SetGlobalEnergy(0);
  goto(0);

InitializePlayer: // Par(0)
  // Drone erstellen
  SetVar(0,CreateObject(_GDR,0,0));
  // Var(1) ist der Clonk des Spielers
  SetVar(1,GetCrew(Par(0),0));
  SetPosition(GetX(Var(1)),GetY(Var(1)),Var(0));
  // Dronen auf Clonk ausrichten
  SetLocal(0,Var(1),Var(0));
  // Andersrum
  SetLocal(0,Var(0),Var(1));
  // Sender
  SetOwner(Par(0),CreateContents(_RDO,Var(1)));
  // Fertig
  return(1);

Resume:
  Music(0);
  Sound("Fanfare");
  Log("Alle Monster sind besiegt.");
  Message("Alle Monster sind besiegt.|Gratulation!");
  GameOver();
  return(1);

/* Energie */

DoGlobalEnergy: // Par(0)
  return(SetGlobal(0,Sum(Global(0),Par(0))));

SetGlobalEnergy: // Par(0)
  return(SetGlobal(0,Par(0)));

GetGlobalEnergy:
  return(Global(0));