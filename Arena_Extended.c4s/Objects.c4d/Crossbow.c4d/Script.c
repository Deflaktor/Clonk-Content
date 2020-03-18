#strict
/*-- Armbrust --*/

/* Initialisierung */

protected Initialize:
  SetAction("Ready");
  SetPhase(15);
  return(1);

Destroy:
SetPosition(200+Random(LandscapeWidth()-200),0);
return(1);

Test:
if (And(Equal(GetMaterial(0,-10),Material("Earth")),And(Equal(GetMaterial(0,-20),Material("Earth")),Equal(GetMaterial(0,0),Material("Earth")))))
SetPosition(GetX(),0);
if (And(Equal(GetMaterial(0,-10),Material("Water")),And(Equal(GetMaterial(0,-20),Material("Water")),Equal(GetMaterial(0,0),Material("Water")))))
SetPosition(GetX(),0);
SetLocal(0,Local(0)+1);
return(1);

/* Steuerung */

public ControlCommand:
  // Feuern
  if (SEqual(Par(0),"MoveTo"))
    if (GreaterThan(Distance(GetX(),GetY(),Par(2),Par(3)),50))
      return(HaltPushers(),FireAt(Par(2),Par(3)));
  // Keine 
  return(0);

public ControlUp:
  [Zielen: auf]
  if (GreaterThan(GetPhase(),0))
    SetPhase(Sum(GetPhase(),-1));
  return(1);

public ControlDig:
  [Zielen: ab]
  if (LessThan(GetPhase(),19))
    SetPhase(Sum(GetPhase(),+1));
  return(1);

public ControlThrow:
  [Feuern]
  if(Local(0)>1) {
    SetLocal(0);
    Var(0)=CreateContents(XARW);
    SetOwner(GetOwner(Par(0)), Var(0));
  }
  return(Fire());

private HaltPushers:
  while (SetVar(0,FindObject(0,0,0,0,0,0,"Push",this(),0,Var(0))))
    SetComDir(COMD_Stop(),Var(0));
  return(1);
  
/* Feuern */

public Fire: // (BOOL fAuto)
  // Pfeil suchen
  if (Not(SetVar(1,Contents()))) return(Sound("Click"));
  // Austritt berechnen
  SetVar(2, Div( Mul( Sum(GetPhase(),-18), 3), 4) );
  SetVar(3, Div( Mul( GetPhase(), 2), 3) );
  if ( Equal(GetDir(),0) ) SetVar(3, Mul(Var(3),-1) );
  SetVar(6, +3);
  if ( Equal(GetDir(),0) ) SetVar(6, Mul(Var(6),-1) );
  SetVar(4,GetPhase());
  if ( Equal(GetDir(),0) ) SetVar(4, Mul(Var(4),-1) );
  SetVar(5,Sum(GetPhase(),-15));
  SetVar(7, Mul( Var(4), 5) );  
  // Pfeil abfeuern
  Exit(Var(1), Var(4),Var(5),Var(7), Var(3),Var(2),Var(6) );
  ObjectCall(Var(1),"Launch",this());
  // Sicht verfolgen (wenn nicht automatisch)
  if (Not(Par(0)))
    if (Not(Equal(GetPlrView(GetController()),2)))
      SetPlrView(GetController(),Var(1));
  // Sound
  Sound("Arrow");
  // Fertig
  return(1);

private FireAt: // (int iX, int iY, BOOL fAuto)
  // Zielwinkel
  SetVar(0,Angle(GetX(),GetY(),Par(0),Par(1)));
  // Bei größerer Distanz höher zielen
  if (Inside(Sub(Par(0),GetX()),+1,+300))
    SetVar(0,Sub(Var(0),Div(Abs(Sub(Par(0),GetX())),12)));
  if (Inside(Sub(Par(0),GetX()),-300,-1))
    SetVar(0,Sum(Var(0),Div(Abs(Sub(Par(0),GetX())),12)));
  // Zielen
  AimToAngle(Var(0));
  // Feuern
  return(Fire(Par(2)));

private AimToAngle: // (int iAngle)
  // Winkel anpassen
  SetVar(0,Par(0));
  while (GreaterThan(Var(0),180)) SetVar(0,Sum(Var(0),-360));
  // Richtung
  if (GreaterThan(Var(0),0)) SetDir(DIR_Right());
  if (LessThan(Var(0),0)) SetDir(DIR_Left());
  // Zielrichtung
  SetPhase(BoundBy( Div(Mul(20,Abs(Var(0))),90), 0,19));
  // Fertig
  return(1);
    
/* Laden */

protected Collection:
  // Sound
  Sound("Connect");
  // Pakete zerlegen
  if (ObjectCall(Par(0), "IsArrowPack"))
    And(Split2Components(Par(0)), SplitPacks());
  return(1);

private SplitPacks:
  SetVar(0,-1);
  while (SetVar(1, Contents(IncVar(0))))
    if (ObjectCall(Var(1),"UnpackTo"))
      Split2Components(Var(1));
  return(1);

/* Nur Pfeile und Pfeilpakete annehmen */

protected RejectCollect:
  // Pfeile
  if (ObjectCall(Par(1), "IsArrow")) return(0);
  // Pfeilepakete
  if (ObjectCall(Par(1), "IsArrowPack")) return(0);
  // Objekt ablehnen
  return(1);
