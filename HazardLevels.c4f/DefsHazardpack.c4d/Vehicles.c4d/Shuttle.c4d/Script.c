/*-- Shuttle --*/
#strict
/* Initialisierung */

protected Initialize:
  SetAction("Hover");
  EnablePlayerControl();
  return(1);

/* Zerstörung */

protected Incineration:
  ChangeDef(SHTB);
  SetAction("Destroyed");
  ObjectCall(CreateObject(EXPL),"Launch",50);
  CastObjects(_DFR,6,100,0,0);
  CastObjects(_DFS,5,100,0,0);
  while (Contents()) Exit(Contents());
  return(1);

/* Projektil-Treffer */

protected RejectCollect: // C4ID id, C4Object *pObject
  // Von innen alles
  if (Contained(Par(1))) return(0);
  // Von außen nur Raketentreffer
  return(Not(ObjectCall(Par(1),"IsMissile")));

/* Konfiguration */

public DisablePlayerControl:
  SetLocal(8,0); return(1);

public EnablePlayerControl:
  SetLocal(8,1); return(1);

private PlayerControlEnabled:
  return(Local(8));

/* HomebaseAutomatic */

public SetHomebaseAutomatic:
  SetLocal(9,Par(0));
  return(1);

private HomebaseAutomaticEnabled:
  return(Local(9));

public PickupCall:
  // Position im Orbit angleichen
  if (LessThan(GetY(),-40)) 
    ForcePosition( this(), Par(0), GetY() );
  // Wartemodus: Kurzstart
  if (SEqual(GetCommand(),"Wait")) SetYDir(-20);
  // Zielkommando
  SetCommand(this(),"MoveTo",0,Par(0),Par(1));
  // Bestätigen
  Sound("ShuttleAcknowledge");
  return(1);

ExecuteHomebaseAutomatic:
  // HomebaseAutomatic nicht aktiv
  if (Not(HomebaseAutomaticEnabled())) return(0);
  // Kein Kommando, Rückkehr zur Basis (Orbit), vorher Mannschaft rauswerfen
  if (Not(GetCommand()))
    if (Not(DispatchCrew()))
      SetCommand(this(),"MoveTo",0,GetX()/*Sum(GetX(),Random(400),-200)*/,-80);
  return(1);

private HomeBaseAutomaticOnContact:
  // HomebaseAutomatic nicht aktiv
  if (Not(HomebaseAutomaticEnabled())) return(0);
  // Anhalten: Bewegungskommando abbrechen, warten
  if (SEqual(GetCommand(),"MoveTo"))
    And( SetComDir(COMD_Down()), SetXDir(0), SetYDir(0), SetCommand(this(),"Wait",0,80) );
  return(1);

private ClearOrders:
  SetCommand(this(),"None");
  return(1);

/* Steuerung */

ContainedLeft:
  // Steuerung deaktiviert
  if (Not(PlayerControlEnabled())) return(0);
  // Befehle abbrechen
  ClearOrders();
  // Flugrichtung
  SetComDir(COMD_Left());
  // Aktion
  if (SEqual(GetAction(),"Hover"))
    if (Equal(GetDir(),DIR_Left()))
      SetAction("LowerNose");
  if (SEqual(GetAction(),"Flight"))
    if (Equal(GetDir(),DIR_Right()))
      And( SetAction("RaiseNose"), SetComDir(COMD_Stop()) );
  if (SEqual(GetAction(),"Hover"))
    if (Equal(GetDir(),DIR_Right()))
      And( SetAction("Turn"), SetDir(DIR_Left()) );
  return(1);

ContainedRight:
  // Steuerung deaktiviert
  if (Not(PlayerControlEnabled())) return(0);
  // Befehle abbrechen
  ClearOrders();
  // Flugrichtung
  SetComDir(COMD_Right());
  // Aktion
  if (SEqual(GetAction(),"Hover"))
    if (Equal(GetDir(),DIR_Right()))
      SetAction("LowerNose");
  if (SEqual(GetAction(),"Flight"))
    if (Equal(GetDir(),DIR_Left()))
      And( SetAction("RaiseNose"), SetComDir(COMD_Stop()) );
  if (SEqual(GetAction(),"Hover"))
    if (Equal(GetDir(),DIR_Left()))
      And( SetAction("Turn"), SetDir(DIR_Right()) );
  return(1);

ContainedUp:
  // Steuerung deaktiviert
  if (Not(PlayerControlEnabled())) return(0);
  // Befehle abbrechen
  ClearOrders();
  // Flugrichtung
  SetComDir(COMD_Up());
  return(1);

ContainedDown:
  // Steuerung deaktiviert
  if (Not(PlayerControlEnabled())) return(0);
  // Befehle abbrechen
  ClearOrders();
  // Flugrichtung
  SetComDir(COMD_Down());
  return(1);

ContainedDownDouble:
  // Tür aktivieren
  SetComDir(COMD_Stop());
  SetXDir(0);
  ActivateEntrance();
  return(1);

/* Checks & Automatik */

protected Automatic: // TimerCall
  ForceMaximumAltitude();
  ExecuteHomebaseAutomatic();
  if (PlayerControlEnabled()) PilotCheck();
  CheckDirection();
  return(1);

private ForceMaximumAltitude:
  if (LessThan(GetY(),-100)) SetPosition(GetX(),-100);
  return(1);

private PilotCheck:
  if (Not(FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,this())))
    SetComDir(COMD_Down());
  return(1);

private CheckDirection:
  if (GreaterThan(GetXDir())) 
    if (Equal(GetDir(),DIR_Left()))
      if (SEqual(GetAction(),"Hover"))
        SetAction("Turn",0,0,0,SetDir(DIR_Right()));
  if (LessThan(GetXDir())) 
    if (Equal(GetDir(),DIR_Right()))
      if (SEqual(GetAction(),"Hover"))
        SetAction("Turn",0,0,0,SetDir(DIR_Left()));
  return(1);

/* Kontakt */

protected ContactLeft:
  if (SEqual(GetAction(),"Flight")) SetAction("RaiseNose");
  OnContact();
  return(0);

protected ContactRight:
  if (SEqual(GetAction(),"Flight")) SetAction("RaiseNose");
  OnContact();
  return(0);

protected ContactBottom: 
  OnContact();
  return(0);

protected ContactTop: 
  OnContact();
  return(0);

private OnContact:
  HomeBaseAutomaticOnContact();
  return(1);

/* Aktivität & Reaktion */

private FlightThrust:
  SetVar(0,Min(Sum(GetActTime(),20),100));
  if (Equal(GetDir(),DIR_Left())) SetVar(0,Mul(Var(0),-1));
  SetXDir(Var(0));  
  return(1);

protected Hit:
  Sound("ShuttleHit");
  return(1);

private DispatchCargo:
  // Ladung auswerfen
  while (SetVar(0,Contents(Var(1))))
    And( ActivateEntrance(), SetCommand(Var(0),"Exit"), SetVar(1,Sum(Var(1),+1)) );
  return(1);

DispatchCrew:
  // Mannschaft und Sender auswerfen
  SetVar(1,-1); SetVar(2,0);
  while ( SetVar(0,Contents(SetVar(1,Sum(Var(1),+1)))) ) {
    if(BitAnd(GetOCF(Var(0)),OCF_CrewMember())) {
      SetCursor(GetOwner(Var(0)),Var(0));
      ActivateEntrance();
      SetCommand(Var(0),"Exit");
      SetVar(2,1);
    }
    if(Equal(GetID(Var(0)),_RDO)) {
      ActivateEntrance();
      SetCommand(Var(0),"Exit");
      SetVar(2,1);
    }
  }
  return(Var(2));

/* Eingang & Türsteuerung */

protected ActivateEntrance:
  // Eingang kann von innen nur über ContainedDownDouble aktiviert werden (nicht ContainedDown)
  if (And( Contained(Par(0)), CrewMember(Par(0)) )) return(1);
  // Tür kann nur beim Schweben geöffnet werden
  if (Not(SEqual(GetAction(),"Hover"))) return(1);
  // Tür öffnen
  SetAction("OpenDoor");
  return(1);

private OpenEntrance: 
  SetEntrance(1); return(1);
private CloseEntrance: 
  SetEntrance(0); return(1);
private SoundOpenDoor: 
  Sound("Airlock1"); return(1);
private SoundCloseDoor: 
  Sound("Airlock2"); return(1);
