#strict
/*-- Große Schwebeplatte --*/

/* Lokale Variablen */

// 0: Horizontale an/aus
// 1: Vertikale an/aus
// 2: ComDir für ResumeTravel, X/Y für SpeedTo
// 3: Y Obergrenze gesetzt
// 4: Y Obergrenze Transfer
// 5: Y Untergrenze Transfer

/* Steuerung */

DigFree:
  DigFreeRect(GetX()-Width()/2, GetY()+4, Width(), 12);
  return(1);
  
Width:
  return(49);

public ControlCommand:
  if(Not(CheckEnergy()))
    return(0);
  // Bewegungskommando vertikal
  if (SEqual(Par(0),"MoveTo"))
    if (Vertical())
      if (Inside(Sub(Par(2),GetX()),-16,+16))
        if (LessThan(Par(3),GetY()))
          return(SetComDir(COMD_Up()));
  if (SEqual(Par(0),"MoveTo"))
    if (Vertical())
      if (Inside(Sub(Par(2),GetX()),-16,+16))
        if (GreaterThan(Par(3),GetY()))
          return(SetComDir(COMD_Down()));
  // Bewegungskommando horizontal
  if (SEqual(Par(0),"MoveTo"))
    if (Horizontal())
      if (Inside(Sub(Par(3),GetY()),-16,+16))
        if (LessThan(Par(2),GetX()))
          return(SetComDir(COMD_Left()));
  if (SEqual(Par(0),"MoveTo"))
    if (Horizontal())
      if (Inside(Sub(Par(3),GetY()),-16,+16))
        if (GreaterThan(Par(2),GetX()))
          return(SetComDir(COMD_Right()));
  // Andere Kommandos nicht auswerten
  return(0);

public ControlUp:
  if(Not(CheckEnergy()))
    return(1);
  Sound("Click");
  if (Not(Vertical())) return(Stop());
  SetComDir(COMD_Up());
  SetXDir(0);
  SetAction("Travel");
  return(1);

public ControlDownSingle:
  if(Not(CheckEnergy()))
    return(1);
  Sound("Click");
  if (Not(Vertical())) return(Stop());
  SetComDir(COMD_Down());
  SetXDir(0);
  SetAction("Travel");
  return(1);

public ControlLeft:
  if(Not(CheckEnergy()))
    return(1);
  Sound("Click");
  if (Not(Horizontal())) return(Stop());
  SetComDir(COMD_Left());
  SetYDir(0);
  SetAction("Travel");
  return(1);

public ControlRight:
  if(Not(CheckEnergy()))
    return(1);
  Sound("Click");
  if (Not(Horizontal())) return(Stop());
  SetComDir(COMD_Right());
  SetYDir(0);
  SetAction("Travel");
  return(1);

/* Kontakt */

protected ContactTop:
  if (Not(Vertical())) return(Stop());
  Wait(COMD_Down());
  return(1);

protected ContactBottom:
  if (Not(Vertical())) return(Stop());
  if (And(Horizontal(),Vertical())) return(Stop()); 
  Wait(COMD_Up());
  return(1);

protected ContactLeft:
  if (Not(Horizontal())) return(Stop());
  Wait(COMD_Right());
  return(1);

protected ContactRight:
  if (Not(Horizontal())) return(Stop());
  Wait(COMD_Left());
  return(1);

/* Konfiguration */

public EnableHorizontal:   
  return(SetLocal(0,1));

public DisableHorizontal:   
  return(SetLocal(0,0));

public EnableVertical:   
  return(SetLocal(1,1));

public DisableVertical:
  return(SetLocal(1,0));

private Horizontal:
  return(Local(0));

private Vertical:
  return(Local(1));

public SetYTop:
  return(SetLocal(3,Par(0)));
  
private YTop:
  return(Local(3));

/* Kommandos */

public Stop:
  SetAction("Travel");
  SetComDir(COMD_Stop());
  SetXDir(0); SetYDir(0);
  return(1);

private Wait: // Par(0) ist anschließende ComDir
  Stop();
  // Aktion Wait ruft als EndCall ResumeTravel auf
  SetAction("Wait"); 
  // ResumeTravel benutzt Local(2) als ComDir
  SetLocal(2,Par(0)); 
  return(1);  

private ResumeTravel: // EndCall von Aktion Wait
  if(Not(CheckEnergy()))
    return(1);
  SetAction("Travel");
  SetComDir(Local(2));
  return(1);

private Automatic: // EndCall von Aktion Travel
  // Keine Automatik, wenn ein Clonk mitfährt
  if (Passenger()) return(0); 
  // Zu einem wartenden Clonk hinfahren
  if (SpeedToVertical()) return(1);
  // Eigenständige Bewegung beginnen
  if (SelfTravel()) return(1);
  return(0);

private SelfTravel:
  if(Not(CheckEnergy()))
    return(1);
  // Nur wenn angehalten
  if (Not(Equal(GetComDir(),COMD_Stop()))) return(0);
  // Eigenständige Bewegung je nach zugelassener Richtung beginnen
  if ( And( Horizontal(), Not(Vertical()) ) ) SetComDir(COMD_Left());
  if ( And( Vertical(), Not(Horizontal()) ) ) SetComDir(COMD_Up());
  if ( And( Vertical(), Horizontal() ) ) SetComDir(COMD_Down());
  return(1);

private SpeedToVertical:
  if(Not(CheckEnergy()))
    return(1);
  if (And(Vertical(),Horizontal())) return(0);
  if (Not(Vertical())) return(0);
  if (Not(SetVar(0,FindObject(0, -50,-1000,100,2000, OCF_CrewMember(),0,0,NoContainer())))) return(0);
  if (Not(Equal(GetComDir(Var(0)),COMD_Stop()))) return(0);
  SetAction("SpeedToY");
  SetLocal(2, Max( GetY(Var(0)), Sum(YTop(),-10) ) ); // Speed to target y or YTop
  return(1);

/* Aktion */

private CheckYTop: // PhaseCall von Travel
  if (GreaterThan( GetY(), Sum(YTop(),-10) )) return(0);
  ForcePosition(this(),GetX(),Sum(YTop(),-10));
  ContactTop();
  return(1);

private SpeedToY: // StartCall von SpeedToY
  SetYDir(BoundBy(Sub(Local(2),GetY()),-50,+50));
  if (Inside(Sub(Local(2),GetY()),-4,+2)) Stop();
  return(1);

private SpeedToX: // StartCall von SpeedToX
  SetYDir(0);
  SetXDir(BoundBy(Sub(Local(2),GetX()),-50,+50));
  if (Inside(Sub(Local(2),GetX()),-10,+10)) Stop();
  return(1);

/* Status */

public Passenger:
  return( FindObject(0, -Width()/2,-13,Width(),16, OCF_CrewMember(),0,0,NoContainer()) );

/* Initialisierung */

protected Initialize:
  SetAction("Travel");
  return(1);
  
/* Transfer */

protected UpdateTransferZone:
  if(Not(CheckEnergy()))
    return(SetTransferZone());
  // Nur vertikale Schwebeplatten
  if (Local(0)) return(0);
  // Obergrenze ermitteln
  var yt, yb;
  yt = Local(3);
  if(!Local(3)) {
    var y = GetY();
    while (y > 5 && !GBackSolid(0,y-GetY()) )
      y-=5;
	yt=y+30;
  }
  yb = Local(5);
  // Untergrenze ermitteln
  if(!yb) {
    var y = GetY()+15;
    while (y < LandscapeHeight()-5 && !GBackSolid(0,y-GetY()) )
      y+=5;
	yt=y;
  }
  // Transferzone setzen
  SetTransferZone(-Width()/2,yt-GetY()-40,Width(),yb-yt+50);
  // Ober- und Untergrenze speichern
  SetLocal(4,yt);
  SetLocal(5,yb);
  return(1);

protected ControlTransfer: // C4Object* pObj, int iTx, int iTy
  
  // Durchgang am Boden des Fahrstuhlschachts: nicht warten
  if (Inside(Sub(GetY(Par(0)),Local(5)),-10,+10))
    if (Inside(Sub(Par(2),Local(5)),-10,+10))
      return(0);

  // Zielposition
  SetVar(1,Par(2));
  
  // Maximale Obergrenze
  SetVar(1,Max(Var(1),Local(4)));

  // Fahrstuhl mit Clonk an Zielposition: anhalten, erledigt
  if (Inside(Sub(Var(1),GetY()),-5,+5))
    if (Passenger())
      return(0,Stop());

  // Fahrstuhl noch nicht beim Clonk: warten
  if (Not(Inside(Sub(GetY(),GetY(Par(0))),-15,+15)))
    return(1);

  // Fahrstuhl nur in der Mitte anfassen
  if (Not(Inside(Sub(GetX(),GetX(Par(0))),-15,+15)))
    return(AddCommand(Par(0),"MoveTo",this(),0,0,0,15));

  // Fahrstuhl anfassen
  if (Not( And(SEqual(GetAction(Par(0)),"Push"),Equal(GetActionTarget(0,Par(0)),this())) ))
    return(AddCommand(Par(0),"Grab",this()));
  
  // Fahrstuhl zur Zielposition steuern
  if (LessThan(Var(1),GetY())) 
    return(SetComDir(COMD_Up()));  
  return(SetComDir(COMD_Down()));

CheckEnergy:
if(Not(Global(6)))
return(1);
if (Not(GameCall("MainEnergySupply", this()))) return(0);
return(1);