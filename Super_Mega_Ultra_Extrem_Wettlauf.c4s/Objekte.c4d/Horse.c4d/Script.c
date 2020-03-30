/*-- Pferd: HORS,HRSK,HRSW --*/

/* Locals */

// 0 Gangart: 0 Gehen, 1 Trab, 2 Galopp, 3,4,5 Ziehen
// 1 Gesattelt (Satteltyp)

/* IDs */

private ID_Unsaddled: return(HORS);
private ID_Dead: return(DHRS);

/* Initialisierung */

Destruction:
  ObjectSetAction(GetRider(),"Walk");
  return(1);

Destroy:
  CastObjects(BLUT, 40, 20);
  CastObjects(MEAT, 2, 20);
  SetVar(0,GetRider());
  RemoveObject();
  ObjectSetAction(Var(0),"Walk");
  ObjectCall(Var(0),"Destroy");
  return(1);

Verschwinde:
  SetVar(0,GetRider());
  RemoveObject();
  ObjectSetAction(Var(0),"Walk");
  ObjectCall(Var(0),"Verschwinde");
  return(1);

protected Initialize:
  SetAction("Walk");
  SetDir(DIR_Left());
  if (Random(2)) SetDir(DIR_Right());
  SetComDir(COMD_Stop());
  SetLocal(0,0);
  // Satteltyp initialisieren
  if (Equal(GetID(this()),HRSK)) SetLocal(1,KSDL);
  if (Equal(GetID(this()),HRSW)) SetLocal(1,SADL);
  return(1);

public Redefine:
  ChangeDef(Par(0));
  SetAction("Walk");
  return(1);

/* TimerCall */

private Activity:
  // Angehalten: Stehen
  if (Equal(GetComDir(),COMD_Stop()))
    if (Equal(GetXDir(),0))
      if (Or(SEqual(GetAction(),"Walk"),SEqual(GetAction(),"Trot"),SEqual(GetAction(),"Gallop")))
        SetAction("Stand");
  // Bewegungskommando: Aktion anpassen
  if (SEqual(GetCommand(),"MoveTo"))
    MoveToAdjustAction();
  return(1);

private MoveToAdjustAction:
  // Losgehen
  if (SEqual(GetAction(),"Stand"))
    return(SetAction("Walk"));
  // Traben
  if (GreaterThan(Abs(Distance(GetX(),GetY(),GetCommand(0,2),GetCommand(0,3))),75))
    if (SEqual(GetAction(),"Walk"))
      return(SetAction("Trot"));
  // Galoppieren
  if (GreaterThan(Abs(Distance(GetX(),GetY(),GetCommand(0,2),GetCommand(0,3))),150))
    if (SEqual(GetAction(),"Trot"))
      return(SetAction("Gallop"));
  return(0);
  


/* Reiten */

protected ActivateEntrance:
  // Nur ein Reiter zur Zeit
  if (GetRider()) return(0);
  // Nur im Stehen, Gehen, Schwimmen, Ziehen
  if (Not(Or( SEqual(GetAction(),"Walk"), SEqual(GetAction(),"Stand"), 
              SEqual(GetAction(),"Swim"), SEqual(GetAction(),"Pull") ))) 
    return(0);
  // Reiter kann nur mit Sattel reiten
  if (ObjectCall(Par(0),"NeedSaddle"))
    if (Not(IsSaddled()))
      return(0,Message("%s kann nicht|ohne Sattel reiten.",Par(0),GetName(Par(0))));
  // Aufsitzen
  if (Not(ObjectSetAction(Par(0),"Ride",this())))
    return(NoGoodRider(Par(0)));
  // Clonkposition anpassen
  ForcePosition(Par(0),GetX(),Sum(GetY(),-5));
  // Erfolg
  return(1);

/* Steuerung */

public ControlLeft:
  [Führen]
  if(GameCall("DontMove")) return(1);
  // Direkte Steuerung löscht Kommandos
  ClearCommands();
  // Gehen/Stehen/Ziehen: Wenden
  if (Or( SEqual(GetAction(),"Walk"), SEqual(GetAction(),"Stand"), SEqual(GetAction(),"Pull") ))
    if (Equal(GetDir(),DIR_Right())) 
      return(TurnLeft());
  // Ziehen: Losgehen
  if (SEqual(GetAction(),"Pull"))
    if (Equal(GetComDir(),COMD_Stop()))
      return(SetComDir(COMD_Left()));  
  // Stehen: Losgehen
  if (SEqual(GetAction(),"Stand")) 
    return(SetLocal(0,0),SetAction("Walk"),SetComDir(COMD_Left()));
  // Gehen: Trotten (nur durch Reiter)
  if (SEqual(GetAction(),"Walk"))
    if (Equal(GetDir(),DIR_Left())) 
      if (Equal(Par(0),GetRider()))
        return(SetLocal(0,1),SetAction("Trot"),SetComDir(COMD_Left()));
  // Ziehen: Ziehen2
  if (SEqual(GetAction(),"Pull"))
    if (Equal(GetDir(),DIR_Left())) 
      return(SetLocal(0,4),SetAction("Pull2"),SetComDir(COMD_Left()),SetPhase(Random(10)));
  // Ziehen2: Ziehen3
  if (SEqual(GetAction(),"Pull2"))
    if (Equal(GetDir(),DIR_Left())) 
      return(SetLocal(0,5),SetAction("Pull3"),SetComDir(COMD_Left()),SetPhase(Random(10)));
  // Trotten: Galoppieren (nur durch Reiter)
  if (SEqual(GetAction(),"Trot"))
    if (Equal(GetDir(),DIR_Left())) 
      if (Equal(Par(0),GetRider()))
        return(SetLocal(0,2),SetAction("Gallop"),SetComDir(COMD_Left()));
  // Galoppieren: Trotten
  if (SEqual(GetAction(),"Gallop"))
    if (Equal(GetDir(),DIR_Right())) 
      return(SetLocal(0,1),SetAction("Trot"));  
  // Trotten: Gehen
  if (SEqual(GetAction(),"Trot"))
    if (Equal(GetDir(),DIR_Right())) 
      return(SetLocal(0,0),SetAction("Walk"));  
  // Ziehen2: Ziehen
  if (SEqual(GetAction(),"Pull2"))
    if (Equal(GetDir(),DIR_Right())) 
      return(SetLocal(0,3),SetAction("Pull"),SetPhase(Random(10)));  
  // Ziehen3: Ziehen2
  if (SEqual(GetAction(),"Pull3"))
    if (Equal(GetDir(),DIR_Right())) 
      return(SetLocal(0,4),SetAction("Pull2"),SetPhase(Random(10)));  
  // Schwimmen: Richtung bestimmen
  if (SEqual(GetAction(),"Swim"))
    return(SetComDir(COMD_Left()));  
  // Keine Steuerung 
  return(0);

public ControlRight:
  [Führen]
  if(GameCall("DontMove")) return(1);
  // Direkte Steuerung löscht Kommandos
  ClearCommands();
  // Gehen/Stehen/Ziehen: Wenden
  if (Or( SEqual(GetAction(),"Walk"), SEqual(GetAction(),"Stand"), SEqual(GetAction(),"Pull") ))
    if (Equal(GetDir(),DIR_Left())) 
      return(TurnRight());
  // Ziehen: Losgehen
  if (SEqual(GetAction(),"Pull"))
    if (Equal(GetComDir(),COMD_Stop()))
      return(SetComDir(COMD_Right()));  
  // Stehen: Losgehen
  if (SEqual(GetAction(),"Stand")) 
    return(SetLocal(0,0),SetAction("Walk"),SetComDir(COMD_Right()));
  // Gehen: Trotten (nur durch Reiter)
  if (SEqual(GetAction(),"Walk"))
    if (Equal(GetDir(),DIR_Right())) 
      if (Equal(Par(0),GetRider()))
        return(SetLocal(0,1),SetAction("Trot"),SetComDir(COMD_Right()));
  // Ziehen: Ziehen2
  if (SEqual(GetAction(),"Pull"))
    if (Equal(GetDir(),DIR_Right())) 
      return(SetLocal(0,4),SetAction("Pull2"),SetComDir(COMD_Right()),SetPhase(Random(10)));
  // Ziehen2: Ziehen3
  if (SEqual(GetAction(),"Pull2"))
    if (Equal(GetDir(),DIR_Right())) 
      return(SetLocal(0,5),SetAction("Pull3"),SetComDir(COMD_Right()),SetPhase(Random(10)));
  // Trotten: Galloppieren (nur durch Reiter)
  if (SEqual(GetAction(),"Trot"))
    if (Equal(GetDir(),DIR_Right())) 
      if (Equal(Par(0),GetRider()))
        return(SetLocal(0,2),SetAction("Gallop"),SetComDir(COMD_Right()));
  // Galoppieren: Trotten
  if (SEqual(GetAction(),"Gallop"))
    if (Equal(GetDir(),DIR_Left())) 
      return(SetLocal(0,1),SetAction("Trot"));  
  // Trotten: Gehen
  if (SEqual(GetAction(),"Trot"))
    if (Equal(GetDir(),DIR_Left())) 
      return(SetLocal(0,0),SetAction("Walk"));  
  // Ziehen2: Ziehen
  if (SEqual(GetAction(),"Pull2"))
    if (Equal(GetDir(),DIR_Left())) 
      return(SetLocal(0,3),SetAction("Pull"),SetPhase(Random(10)));  
  // Ziehen3: Ziehen2
  if (SEqual(GetAction(),"Pull3"))
    if (Equal(GetDir(),DIR_Left())) 
      return(SetLocal(0,4),SetAction("Pull2"),SetPhase(Random(10)));  
  // Schwimmen: Richtung bestimmen
  if (SEqual(GetAction(),"Swim"))
    return(SetComDir(COMD_Right()));  
  // Keine Steuerung 
  return(0);

public ControlUp:
  [Springen]
  if(GameCall("DontMove")) return(1);
  // Nur im Gallop
  if (SEqual(GetAction(),"Gallop")) return(Jump());
  // Kein Sprung
  return(0);

public ControlDownSingle:
  [Anhalten]
  if(GameCall("DontMove")) return(1);
  // Direkte Steuerung löscht Kommandos
  ClearCommands();
  // Ziehen: Anhalten
  if (SEqual(GetAction(),"Pull"))
    return(SetComDir(COMD_Stop()));
  // Galloppieren: Trotten
  if (SEqual(GetAction(),"Gallop"))
    return(SetLocal(0,1),SetAction("Trot"));  
  // Trotten: Gehen
  if (SEqual(GetAction(),"Trot"))
    return(SetLocal(0,0),SetAction("Walk"));  
  // Ziehen2: Ziehen
  if (SEqual(GetAction(),"Pull2"))
    return(SetLocal(0,3),SetAction("Pull"),SetPhase(Random(10)));  
  // Ziehen3: Ziehen2
  if (SEqual(GetAction(),"Pull3"))
    return(SetLocal(0,4),SetAction("Pull2"),SetPhase(Random(10)));  
  // Gehen: Anhalten  
  if (SEqual(GetAction(),"Walk")) 
    return(SetAction("Stand"),SetComDir(COMD_Stop()));
  // Keine Steuerung
  return(0);

public ControlDownDouble:
  [Absitzen]
  if(GameCall("DontMove")) return(1);
  // Direkte Steuerung löscht Kommandos
  ClearCommands();
  // Reiter: absitzen
  //if (Equal(Par(0),GetRider()))
  //  return(ObjectSetAction(Par(0),"Walk"));
  // Keine Steuerung
  return(0);

public ControlDigDouble:
  [Anspannen]
  if(GameCall("DontMove")) return(1);
  // Direkte Steuerung löscht Kommandos
  ClearCommands();
  // Angespannt: ausspannen
  if (SEqual(GetAction(),"Pull"))
    return(DisconnectWagon());
  // Anspannen/Satteln: nur im Stehen oder Gehen
  if (Not(Or( SEqual(GetAction(),"Walk"), SEqual(GetAction(),"Stand") ))) 
    return(0);
  // Wagen suchen und anspannen
  if (SetVar(0,FindHorseWagon()))
    return(ConnectWagon(Var(0)));
  // Sattel abnehmen
  if (IsSaddled())
    if (Unsaddle())
      return(1);
  // Satteln (Sattelobjekt im Aufrufer aktivieren)
  if (SetVar(0,FindSaddleIn(Par(0))))
    if (ObjectCall(Var(0),"Activate",Par(0)))
      return(1);
  // Keine Aktion
  return(0);    

public ControlCommand: // const char* szCommand, C4Object* pTarget, int iTx, int iTy
  if(GameCall("DontMove")) return(1);
  // Kommando MoveTo: gegebenenfalls wenden
  if (SEqual(Par(0),"MoveTo"))
    if (GreaterThan(Par(2),GetX()))
      TurnRight();
  if (SEqual(Par(0),"MoveTo"))
    if (LessThan(Par(2),GetX()))
      TurnLeft();
  // Kommando setzen
  return(SetCommand(this(),Par(0),Par(1),Par(2),Par(3)));

/* Anspannen und satteln */

private DisconnectWagon:
  ObjectCall(GetActionTarget(),"Disconnect",this());
  SetLocal(0,0);
  SetAction("Walk");
  return(1);

private ConnectWagon: // C4Object *pWagon
  SetLocal(0,3); 
  SetAction("Pull",Par(0));
  ObjectCall(Par(0),"Connect",this());
  return(1);

public Saddle: // Par(0) Neuer Pferdtyp, Par(1) Satteltyp
  // Bereits gesattelt
  if (IsSaddled()) return(0);
  // Satteln: nur im Stehen, Gehen, Ziehen
  if (Not(Or( SEqual(GetAction(),"Walk"), SEqual(GetAction(),"Stand"), SEqual(GetAction(),"Pull") ))) 
    return(0);
  // Nur ohne Reiter
  if (GetRider()) return(0);
  // Satteln
  Redefine(Par(0));
  // Satteltyp speichern
  SetLocal(1,Par(1));
  // Sound
  Sound("Connect");
  return(1);

public Unsaddle:
  // Nicht gesattelt
  if (Not(IsSaddled())) return(0);
  // Nur ohne Reiter
  if (GetRider()) return(0);
  // Erst Satteltasche leeren
  if (Contents())
    return(0,Message("Satteltasche enthält|noch Objekte!",this()));
  // Sattel abnehmen
  Redefine(ID_Unsaddled());  
  CreateObject(Local(1),0,+8);
  SetLocal(1,0);
  Sound("Connect");
  return(1);

private TurnRight:
  // Wenden aus Gehen, Stehen, Ziehen
  if (Equal(GetDir(),DIR_Left()))
    if (Or( SEqual(GetAction(),"Walk"), SEqual(GetAction(),"Stand"), SEqual(GetAction(),"Pull") ))
      SetAction("Turn");
  // Richtung
  SetDir(DIR_Right());
  SetComDir(COMD_Right());
  return(1);

private TurnLeft:
  // Wenden aus Gehen, Stehen, Ziehen
  if (Equal(GetDir(),DIR_Right()))
    if (Or( SEqual(GetAction(),"Walk"), SEqual(GetAction(),"Stand"), SEqual(GetAction(),"Pull") ))
      SetAction("Turn");
  // Richtung
  SetDir(DIR_Left());
  SetComDir(COMD_Left());
  return(1);

private ClearCommands:
  SetCommand(this(),"None");
  return(1);

/* Einwirkungen */

protected Damage:
  // Starker Treffer
  if (GreaterThan(Par(0),10))
    SetAction("Rise");
  // Tot
  if (GreaterThan(GetDamage(),100))
    Death();
  // Wiehern
  Sound("HorseNeigh*");
  return(1);    
    
private Collision:
  SetAction("Tumble");
  DoDamage(+5);
  return(1);

public Death:
  // Inhalt auswerfen
  while (Contents()) Exit(Contents());
  // Gegebenenfalls Sattel verlieren
  Unsaddle();
  // Verwandeln
  ChangeDef(ID_Dead());
  SetAction("Dead");
  SetDir(DIR_Left());
  return(1);

private LiquidDamage:
  // Material abfragen
  if (Equal(SetVar(0,GetMaterial()),-1)) return(0);
  // Säure/Lava (leider hardgecodet)
  if (Or( Equal(Var(0),Material("Acid")),Equal(Var(0),Material("Lava")),Equal(Var(0),Material("DuroLava")) ))
    DoDamage(+8);
  return(1);
  

/* Kontakt */

protected ContactLeft:
  // Kollision
  if (Not(Inside(GetXDir(),-30,+30))) return(Collision());
  // Wenden
  TurnRight(); 
  return(1);
  
protected ContactRight:
  // Kollision
  if (Not(Inside(GetXDir(),-30,+30))) return(Collision());
  // Wenden
  TurnLeft(); 
  return(1);
    
/* Aktionen */

private Pulling:
  // Zielobjekt verloren
  if (Not(GetActionTarget()))
    return(DisconnectWagon());
  // Wagen wenden
  if (Equal(GetDir(GetActionTarget()),DIR_Left()))
    if (GreaterThan(GetX(),GetX(GetActionTarget())))
      ObjectCall(GetActionTarget(),"TurnRight");
  if (Equal(GetDir(GetActionTarget()),DIR_Right()))
    if (LessThan(GetX(),GetX(GetActionTarget())))
      ObjectCall(GetActionTarget(),"TurnLeft");
  // Geschwindigkeit und Geräusch
  SetPhysical("Walk",50000,2);
  Sound("HorseWalk*");
  return(1);  
  
private Pulling2:
  // Zielobjekt verloren
  if (Not(GetActionTarget()))
    return(DisconnectWagon());
  // Wagen wenden
  if (Equal(GetDir(GetActionTarget()),DIR_Left()))
    if (GreaterThan(GetX(),GetX(GetActionTarget())))
      ObjectCall(GetActionTarget(),"TurnRight");
  if (Equal(GetDir(GetActionTarget()),DIR_Right()))
    if (LessThan(GetX(),GetX(GetActionTarget())))
      ObjectCall(GetActionTarget(),"TurnLeft");
  // Geschwindigkeit und Geräusch
  SetPhysical("Walk",70000,2);
  Sound("HorseTrot*");
  return(1);  
  
private Pulling3:
  // Zielobjekt verloren
  if (Not(GetActionTarget()))
    return(DisconnectWagon());
  // Wagen wenden
  if (Equal(GetDir(GetActionTarget()),DIR_Left()))
    if (GreaterThan(GetX(),GetX(GetActionTarget())))
      ObjectCall(GetActionTarget(),"TurnRight");
  if (Equal(GetDir(GetActionTarget()),DIR_Right()))
    if (LessThan(GetX(),GetX(GetActionTarget())))
      ObjectCall(GetActionTarget(),"TurnLeft");
  // Geschwindigkeit und Geräusch
  SetPhysical("Walk",130000,2);
  Sound("HorseGallop*");
  return(1);  
  
private Walking:
  // Vorherige Gangart wieder aufnehmen (nach Sprung oder Wendung)
  if (Equal(Local(0),1)) return(SetAction("Trot"));
  if (Equal(Local(0),2)) return(SetAction("Gallop"));
  if (Equal(Local(0),3)) return(SetAction("Pull"));
  if (Equal(Local(0),4)) return(SetAction("Pull2"));
  if (Equal(Local(0),5)) return(SetAction("Pull3"));
  // Geschwindigkeit und Geräusch
  SetPhysical("Walk",50000,2);
  Sound("HorseWalk*");
  return(1);  
  
private Turning:  
  // Geräusch
  Sound("HorseWalk*");
  return(1);  
  
private Trotting:
  // Geschwindigkeit und Geräusch
  SetPhysical("Walk",90000,2);
  Sound("HorseTrot*");
  // Angehalten (z.B. durch Kollision)
  if (Equal(GetComDir(),COMD_Stop())) return(SetLocal(0,0),SetAction("Stand"));
  return(1);     
  
private Gallopping:
  // Geschwindigkeit und Geräusch
  SetPhysical("Walk",160000,2);
  Sound("HorseGallop*");
  // Angehalten (z.B. durch Kollision)
  if (Equal(GetComDir(),COMD_Stop())) return(SetLocal(0,0),SetAction("Stand"));
  return(1);     
  
private Swimming:
  // Unter Wasser: auftauchen
  if (GBackSemiSolid(0,-5)) SetComDir(COMD_Up());
  // Schaden durch gefährliche Flüssigkeiten
  LiquidDamage();
  // Gangart zurücksetzen
  SetLocal(0,0);
  // Geräusch
  Sound("HorseSplash*");
  return(1);  
  
private Tumbling:
 // Reiter abwerfen
 Verschwinde();
 return(1); 
  
private Rising:
 // Reiter abwerfen 
 Verschwinde();
 return(1); 
    
/* Status */

public IsHorse: return(1);

public GetRider:
  if (SetVar(0,FindObject(0, 0,0,0,0, 0, "RideStill",this()))) return(Var(0));
  return(FindObject(0, 0,0,0,0, 0, "Ride",this()));
  
private NoGoodRider:
  if (BitAnd(GetOCF(Par(0)),OCF_CrewMember()))
    Message("%s kann nicht reiten.",Par(0),GetName(Par(0)));
  return(0);
  
private FindHorseWagon:
  while (SetVar(0,FindObject(0, -50,-20,100,40, 0, 0,0, NoContainer(), Var(0))))
    if (ObjectCall(Var(0),"IsHorseWagon"))
      return(Var(0));
  return(0);
  
public IsStill:
  if (SEqual(GetAction(),"Stand")) return(1);
  if (And(SEqual(GetAction(),"Pull"),Equal(GetComDir(),COMD_Stop()))) return(1);
  return(0);

public IsSaddled:
  return(Local(1));

public FindSaddleIn: // Par(0) in Objekt suchen
  SetVar(0,-1);
  while (SetVar(1,Contents(IncVar(0),Par(0))))
    if (ObjectCall(Var(1),"IsSaddle"))
      return(Var(1));
  return(0);