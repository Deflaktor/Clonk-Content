#strict
/*-- Haubitze --*/

/* Initialisierung */

protected Initialize:
  SetAction("Ready");
  SetPhase(10);
  return(1);

Destroy:
SetPosition(200+Random(LandscapeWidth()-200), 0);
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

public ControlThrow:
  [Feuern]
  return(Fire(Par(0)));

public ControlDig:
  [Zielen: ab]
  if (LessThan(GetPhase(),18))
    SetPhase(Sum(GetPhase(),+1));
  return(1);

private HaltPushers:
  while (SetVar(0,FindObject(0,0,0,0,0,0,"Push",this(),0,Var(0))))
    SetComDir(COMD_Stop(),Var(0));
  return(1);

/* Feuern */

public Fire: // (BOOL fAuto)
  if(Local(0)>5) {
    SetLocal(0);
    Var(0)=CreateContents(GameCall("Zufallsflint"));
  }
  // Projektil
  if (Not(SetVar(1,Contents(0))))
    return(Sound("Click"));

  SetOwner(GetOwner(Par(0)),Var(1));
  // Schießpulver verbrauchen
  // Austritt berechnen
  SetVar(2, Sum(GetPhase(),-18) );
  SetVar(3, Mul(GetPhase(),2) );
  if ( Equal(GetDir(),0) ) SetVar(3, Mul(Var(3),-1) );
  SetVar(4,GetPhase());
  if ( Equal(GetDir(),0) ) SetVar(4, Mul(Var(4),-1) );
  SetVar(5,Sum(GetPhase(),-15));
  // Projektil abfeuern
  Exit(Var(1),Var(4),Var(5),Random(360),Var(3),Var(2),+30);
  // Sicht verfolgen (wenn kein automatischer Schuß)
  if (Not(Par(0)))
    if (Not(Equal(GetPlrView(GetController()),2)))
      SetPlrView(GetController(),Var(1));
  // Sound
  Sound("Blast2");
  // Rauch
  Smoke( Sum(Var(4),Random(11),-5), Sum(Var(5),Random(11),-5), Sum(5,Random(8)) );
  Smoke( Sum(Var(4),Random(11),-5), Sum(Var(5),Random(11),-5), Sum(5,Random(8)) );
  Smoke( Sum(Var(4),Random(11),-5), Sum(Var(5),Random(11),-5), Sum(5,Random(8)) );
  Smoke( Sum(Var(4),Random(11),-5), Sum(Var(5),Random(11),-5), Sum(5,Random(8)) );
  Smoke( Sum(Var(4),Random(11),-5), Sum(Var(5),Random(11),-5), Sum(5,Random(8)) );
  // Fertig
  return(1);

/* Zielfunktionen */

public FireAt: // (int iX, int iY, BOOL fAuto)
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

public AimToAngle: // (int iAngle)
  // Winkel anpassen
  SetVar(0,Par(0));
  while (GreaterThan(Var(0),180)) SetVar(0,Sum(Var(0),-360));
  // Richtung
  if (GreaterThan(Var(0),0)) SetDir(DIR_Right());
  if (LessThan(Var(0),0)) SetDir(DIR_Left());
  // Zielrichtung
  SetPhase(BoundBy( Div(Mul(19,Abs(Var(0))),90), 0,18));
  // Fertig
  return(1);
    
/* Laden */

protected Collection:
  Sound("Connect");
  return(1);

protected RejectCollect:
  // Alles außer Schatzkiste annehmen
  if (GetID(Par(1))==CHST) return(1);
  return(0);
