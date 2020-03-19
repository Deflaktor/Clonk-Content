/*-- Fahrstuhlkorb --*/

#strict

// Local 8: Obergrenze
// Local 9: Untergrenze

local AutoMode;       // Dauerbetrieb
local AutoMoveDir;    // Dauerbetrieb Richtung
local RangeTop;       // Obergrenze
local RangeBottom;    // Untergrenze
local timer;          // Timer

local oElev;          // Das Fahrstuhl-Objekt

local pIgnoreClonkDown; // Von diesem Clonk sollte das n�chste ControlDownSingle ignoriert werden (Notfall-Hack)

local oldWaitingClonk;

/* TimerCall */

protected func Timer() 
{
  timer = (++timer) % 30;
  // Lore fassen
  GrabObjects();
  // Clonks umgreifen lassen
  ChangeClonkGrabs();
  // Feststecken -> Schachtbohrung
  if (Stuck() && GetComDir() != COMD_Stop() && !NoEnergy())
    DigFreeRect(GetX() - 36, GetY() - 13, 72, 26);
  if (!timer) Activity();
}
  
protected func Activity()
{
  UpdateTransferZone();
  // Legacy
  if (Local(8) && !RangeTop) ImportSettings();
  // Fahrstuhl zerst�rt
  // if (!Elevator() || OnFire(Elevator())) { SetAction("Idle"); Incinerate(); return(); }
  // Zu wartenden Clonks fahren
  if (AutoMode == 0 && !Passenger() && !GetCommand())
    MoveToWaitingClonk();
  // Sicherheitscheck: Bewegung ohne Kommando nur bei Schachtbohrung
  if (GetComDir())
    if (!GetCommand() && GetAction() ne "Drill")
      Halt();
  // Fertig
  return(1);
}

private func MoveToWaitingClonk()
{
  // Wartender Clonk da? 
  var oClnk;
  if(!(oClnk = FindWaitingClonk()) ) { 
    oldWaitingClonk = 0;
    return(0);
  }
  if(oldWaitingClonk != oClnk) {
    oldWaitingClonk = oClnk;
	return(0);
  }
  oldWaitingClonk = oClnk;
  
  // Bewegung n�tig?
  if(Abs(GetY(oClnk) - GetY()) < 4 
     && GetAction(oClnk) ne "Swim") return(0);

  // Zielposition bestimmen
  var iTargetY = GetY(oClnk);
  if(GetAction(oClnk) S= "Swim")
    iTargetY -= 2;
  if(GetY() > iTargetY)
    iTargetY -= 3;
  
  // Dorthin fahren
  SetMoveTo(iTargetY);
  return(1);              
}

private func FindWaitingClonk()
{
  var clnk, best;
  while(clnk = FindObject(0, -44, RangeTop - GetY(), 88, 6000, OCF_CrewMember(), 0, 0, NoContainer(), clnk) )
    if(GetComDir(clnk) == COMD_Stop() || (GetAction(clnk) S= "Swim" && Inside(GetXDir(clnk), -5, 5)) ) //(GetComDir(clnk) == COMD_Down() || GetComDir(clnk) == COMD_Up() )) )
      if(GetAction(clnk) S= "Walk" || GetAction(clnk) S= "Push" || GetAction(clnk) S= "Scale" || GetAction(clnk) S= "Hangle" || GetAction(clnk) S= "Swim")
        if(!Hostile(GetController(clnk), GetOwner()) )
        {
          // Nicht erreichbar?
          if(GetY(clnk) < GetY() - 7) if(!PathFree(GetX(), GetY(), GetX(), GetY(clnk)) ) continue;
          if(GetY(clnk) > GetY() + 7) if(!PathFree(GetX(), GetY() + 16, GetX(), GetY(clnk)) ) continue;
          // Priorit�t pr�fen (Cursor hat Priorit�t, sonst n�chster Clonk)
          if(!best)
            best = clnk;
          else if(GetCursor(GetController(clnk)) == clnk)
            best = clnk;
          else if(GetCursor(GetController(best)) != best)
            if(ObjectDistance(clnk) < ObjectDistance(best))
              best = clnk;
        }
  return(best);
}

private func FitsInElevator(pObject)
{
  // Alle (ungedrehten) Vertices des Objekts pr�fen
  var vertexCount = GetDefCoreVal("Vertices", "DefCore", pObject->GetID());
  for (var i = 0; i < vertexCount; i++) 
  {
    var vertexX = GetDefCoreVal("VertexX", "DefCore", pObject->GetID(), i);
    var vertexY = GetDefCoreVal("VertexY", "DefCore", pObject->GetID(), i);
    // Passt nicht
    if (!Inside(vertexX, -36, 35) || !Inside(vertexY, -20, 15)) return(0);
  }
  // Passt
  return(1);  
}

private func GrabObjects()
{
  var pObject, did_grab;
  
  // Fahrzeuge
  while (pObject = FindObject(0, -32, -10, 64, 30, OCF_Grab(), 0, 0, 0, pObject)) 
  {
    // Objekt passt in den Fahrstuhlkorb
    if (FitsInElevator(pObject)) 
    {
      if (!(GetCategory(pObject) & C4D_Vehicle())) continue;
      if (!Inside(GetXDir(pObject, 100), -1, +1)) continue;
      if (pObject->~IsTree() && GetCon(pObject) >= 50) continue;
      if (GetX(pObject) == GetX() && GetY(pObject) == GetY() + 1) continue;
      if (pObject->~IsElevator() ) continue;
      did_grab = true;
      
      GrabAdjustPosition(pObject);
    }
  }
  
  // Gegenst�nde
  var obj;
  var item_ocf = OCF_Collectible() | OCF_NotContained();
  while (obj = FindObject(0, -70, 7, 140, 4, item_ocf, 0, 0, 0, obj)) 
  {
    if (!(GetCategory(obj) & C4D_Object())) continue;
    if (GetYDir(obj) < -2 || !Inside(GetXDir(obj), -2, +2)) continue;
    GrabAdjustPosition(obj);
  }
  
  return(did_grab);
}

private func GrabAdjustPosition(obj) 
{
  var offset = (GetObjHeight(this()) - GetObjHeight(obj)) / 2 - 1;
  var x = GetX();

  if (GetCategory(obj) & C4D_Object()) 
  {
    if(GetOCF(obj) & OCF_HitSpeed1() ) return(0);
    offset = 8 + GetYDir() / 10;
    x = GetX(obj);
  }
  else if (GetID(obj) == LORY)
    offset = -1 + GetYDir() / 10;
//  else if (GetID(obj) == BRDG||GetID(obj) == BRDM
  
  SetSpeed(0, GetYDir() / 20, obj); SetRDir(0, obj);
  SetR(0, obj);
  SetPosition(x, GetY() + offset, obj);
}

private func ChangeClonkGrabs()
{
  var clonk;
  var clonk_ocf = OCF_Living() | OCF_NotContained();
  // Schiebende Clonks suchen
  while (clonk = FindObject(0, -62, -10, 124, 20, clonk_ocf, "Push", 0, 0, clonk)) 
  {
    if (GetComDir(clonk) != COMD_Stop() && GetComDir(clonk) != COMD_Up()) continue;
    if (!Inside(GetXDir(clonk), -2, +2)) continue;
    if (GetCommand(clonk) && GetCommand(clonk) ne "None") continue;
    if (GetMenu(clonk)) continue;
      
    // Geschobenes Objekt pr�fen
    var target = GetActionTarget(0, clonk);
    if (!target) continue;
    if (target->~IsElevator() ) continue;
    if (!Inside(GetX(target), GetX() - 8, GetX() + 8)) continue;
    if (ObjectDistance(this(), target) > 15) continue;
    if (!Inside(GetXDir(target), -2, +2)) continue;
    if (!PathFree(GetX(this()), GetY(this()), GetX(target), GetY(target))) continue;
    if (!FitsInElevator(target)) continue;
      
    // Geschobenes Objekt zentrieren
    GrabAdjustPosition(target);
    // Der Clonk soll nun uns anfassen
    if (!Inside(GetX(clonk) - GetX(), -5, +5)) 
    {
      //SetCommand(clonk, "UnGrab"); unn�tig, wenn wir unten SetCommand benutzen...
      //AppendCommand(clonk, "MoveTo", 0, GetX()); wtf sollte denn dieses MoveTo-Kommando zur oberen Bildschirmkante...?
      SetCommand(clonk, "Grab", this());
      // Hack: der Clonk hat wahrscheinlich soeben erst mit ControlDown angehalten.
      // Das darauf folgende ControlDownSingle sollte nicht als Kommando 'Runter'
      // f�r den Fahrstuhl ausgewertet werden!
      pIgnoreClonkDown = clonk;
    } 
    else 
    {
      SetActionTargets(this(), 0, clonk);
    }
  }
}

private func SetMoveTo(iPos)
{
  if (NoEnergy()) return(1);
  SetAction("Ride"); 
  var iDir = 0;
  if (iPos > GetY()) iDir = +3;
  if (iPos < GetY()) iDir = -3;
  SetCommand(this(),"MoveTo", 0, GetX(), Max(iPos, RangeTop) + iDir);
  SetYDir(0);
  return(1);
}

private func Halt()
{
  if (!Elevator()) { SetAction("Idle"); return(); }
  SetAction("Wait");
  SetCommand(this(),"None");
  SetComDir(COMD_Stop());
  SetYDir(0);
  if (GetY() > RangeBottom) UpdateRangeBottom();
  return(1);
}

private func Drilling()
{
  // Steuermann verloren?
  if (!FindObject(0,0,0,0,0,OCF_CrewMember(),"Push",this()) && !FindObject(0,0,0,0,0,OCF_CrewMember(),"Push",FindObject(LORY)))
    Halt();
  return(1);
}

private func Waiting()
{
  // Dauerbetrieb: selbst�ndig losfahren
  if (AutoMode == 1)
    SelfMovement();
  return(1);
}

private func SelfMovement()
{
  // Selbst�ndig rauf- bzw. runterfahren
  if (AutoMoveDir) SetMoveTo(RangeTop);
  if (!AutoMoveDir) SetMoveTo(LandscapeHeight() - 12);
  AutoMoveDir = !AutoMoveDir;
  return(1);
}


/* Steuerung */

protected func ControlCommand(strCommand, oTarget, iTx, iTy)
{
  if (!Elevator()) return(0);
  // Bewegungskommando vertikal
  if (strCommand eq "MoveTo")
    if (Inside(iTx, GetX()-39, GetX()+39))
      return(SetMoveTo(iTy));
  // Andere Kommandos nicht auswerten
  return(0);
}

protected func ControlCommandFinished()
{
  Halt();
  return(1);
}

private func DoControlDown(pObj)
{
  if (pIgnoreClonkDown == pObj)
    { pIgnoreClonkDown = 0; return(0); }
  pIgnoreClonkDown = 0;
  
  if (!Elevator()) return(0);
  if (NoEnergy()) return(0);
  Sound("Click");
  if (Hostile(GetController(pObj), GetOwner())) return(0);
  SetMoveTo(LandscapeHeight() - 12);
}

private func DoControlUp(pObj)
{
  if (!Elevator()) return(0);
  if (NoEnergy()) return(0);
  Sound("Click");
  if (Hostile(GetController(pObj), GetOwner())) return(0);
  SetMoveTo(RangeTop);
}

private func DoControlStop(pObj)
{
  if (!Elevator()) return(0);
  Sound("Click");
  if (Hostile(GetController(pObj), GetOwner())) return(0);
  Halt();
}

private func DoControlDig(pObj)
{
  if (!Elevator()) return(0);
  if (NoEnergy()) return(0);
  Sound("Click");
  if (Hostile(GetController(pObj), GetOwner())) return(0);
  SetCommand(this(),"None");
  SetAction("Drill");
  SetComDir(COMD_Down());
}

public func DoControlAuto(pObj)
{
  // Kein Fahrstuhl
  if (!Elevator()) return(0);
  // Der Clonk soll uns erst anfassen
  if ((GetAction(pObj) ne "Push") || (GetActionTarget(0, pObj) != this()))
  {
    SetCommand(pObj, "None");
    AddCommand(pObj, "Call", this(), 0,0,0,0, "DoControlAuto", pObj);  
    AddCommand(pObj, "Grab", this());
    return(0);
  }
  // Ein Ger�usch machen
  Sound("Click");
  // Feindliche Clonks k�nnen den Modus nicht �ndern
  if (Hostile(GetController(pObj), GetOwner())) return(0);
  // Modus �ndern
  AutoMode = !AutoMode;
  // Meldung ausgeben
  Message(GetAutoModeString(AutoMode), this());
}        

private func RouteToVehicle(call, caller, silent)
{
  var vehicle;
  while (vehicle = FindVehicle(vehicle)) 
  {
    if (!(GetCategory(vehicle) & C4D_Vehicle())) continue;
    if (!PathFree(GetX(caller), GetY(caller), GetX(vehicle), GetY(vehicle))) continue;
    
    // Kommando 'Werfen'
    if (call eq "ControlThrow") 
    {
      var getput = GetDefGrabPutGet(GetID(vehicle));
      PrivateCall(vehicle, call, caller);
      // Will etwas aus dem Fahrzeug rausnehmen?
      if (ContentsCount(0, caller) == 0 && getput & 2) 
      {
        SetCommand(caller, "Activate", 0, 0, 0, vehicle);
      } 
      // Will etwas ins Fahrzeug reinlegen
      else
      {
        if (getput & 1) 
        {
          SetCommand(caller, "Put", vehicle);
          AppendCommand(caller, "Grab", this());
        }      
      }
      // Kommando �berladen
      return(1);
    } 
    // Anderes Kommando
    else 
    {
      if (!PrivateCall(vehicle, call, caller)) 
      {
        var comd;
        if (call eq "ControlLeft") comd = COMD_Left();
        else if (call eq "ControlRight") comd = COMD_Right();
        if (comd) SetComDir(comd, caller);
      }
    }
    // Aktionsziele des Fahrzeugs setzen
    SetActionTargets(vehicle, 0, caller);
    // Kommando �berladen    
    return(1);
  }
  // Ger�usch
  if (!silent) 
    Sound("Click");
  // Kommando nicht �berladen
  return(0);
}

private func FindVehicle(vehicle) 
{
  return(FindObject(0, -8, -10, 16, 30, OCF_Grab(), 0, 0, 0, vehicle));
}

/* Kontakt */

protected func ContactBottom()
{
  Halt();
  UpdateRangeBottom();
  return(1);
}

protected func ContactTop()
{
  Halt();
  return(1);             
}

/* Initialisierung */

protected func Initialize()
{
  SetAction("Wait");
  UpdateRangeTop();
  UpdateRangeBottom();
}

private func UpdateRangeTop()
{  
  // set Local(8) for backwards compatibility
  Local(8) = RangeTop = GetY();
  UpdateTransferZone();
}

private func UpdateRangeBottom()
{
  var x = GetX(), y = GetY() + 13;
  while(PathFree(x, y, x, y + 5) && y < LandscapeHeight()) y += 5;
  // set Local(9) for backwards compatibility
  RangeBottom = Local(9) = Max(Local(9), y+5);
  UpdateTransferZone();
}

/* Status */

private func Passenger()
{
  // Clonk finden
  var clnk = FindObject(0, -72,-13,144,20, OCF_CrewMember(),0,0,NoContainer());
  if(!clnk) return (0);
  // steht wirklich auf dem Fahrstuhl?
  if(GetProcedure(clnk) ne "WALK") return (0);
  return (clnk);
}

private func Elevator()
{
  if(!oElev || GetActionTarget(0, oElev) != this())
    oElev = FindObject(0,0,0,0,0,0,"LiftCase",this());
  return(oElev);
}

private func NoEnergy()
{
  if (EnergyCheck(1000,Elevator())) return(0);
  Halt();
  //Sound("ElevatorNoEnergy");
  return(1);
}

public func IsElevator() { return(1); }

/* Transfer */

protected func UpdateTransferZone()
{         
  if (!Elevator()) return(SetTransferZone());
  SetTransferZone(-36, GetY(oElev) - GetY(), 72, RangeBottom - GetY(oElev) + 12);
  return(1);
}

protected func ControlTransfer(pObj, iTx, iTy)  
{
  
  // Durchgang am Boden des Fahrstuhlschachts: nicht warten
  if (Inside(GetY(pObj) - RangeBottom, -10, +10))
    if (Inside(iTy - RangeBottom, -10, +10))
      return(0);

  // Maximale Obergrenze Zielposition durch Fahrstuhl
  if (!Elevator()) return(0);
  iTy = Max(iTy, GetY(oElev) + 15);

  // Fahrstuhl an Zielposition: erledigt
  if (Inside(iTy - GetY(), -5, +5))
    return(0);

  // Fahrstuhl f�hrt: warten
  if (GetAction() ne "Wait")
    return(1);

  // Fahrstuhl noch nicht beim Clonk: warten
  if (!Inside(GetY() - GetY(pObj), -15, +15))
    return(1);

  // Fahrstuhl nur in der Mitte anfassen
  if (!Inside(GetX() - GetX(pObj), -5, +5))
    return(AddCommand(pObj,"MoveTo",this()));

  // Fahrstuhl anfassen
  if (!InLiquid(pObj) && GetAction(pObj) ne "Push" || GetActionTarget(0, pObj) != this())
    return(AddCommand(pObj,"Grab",this()));
  
  // Fahrstuhl zur Zielposition steuern
  return(SetMoveTo(iTy));
}


/* Zerst�rung: Reduzieren des Fahrstuhls f�r Wiederaufbau/Reparatur */

func Destruction() { if(Elevator()) ObjectCall(Elevator(),"RemoveCase"); }

/* Bei Laden von alten Spielst�nden: Locals zur�ckkopieren */

func ImportSettings()
{
  AutoMode = Local(0);
  AutoMoveDir = Local(7);
  RangeTop = Local(8);
  RangeBottom = Local(9);
}

/* Steuerung */

public func ControlDownSingle(pObj) { [$TxtDown$]       DoControlDown(pObj); return(1); }
public func ControlUp(pObj)         { [$TxtUp$]      DoControlUp(pObj);   return(1); }
public func ControlDigDouble(pObj)  { [$TxtDrillshaft$] DoControlDig(pObj);  return(1); }

public func ControlLeft(pObj) 
{
  [$TxtStop$]
  if (GetAction() ne "Wait") 
  {
    DoControlStop(pObj);
    SetComDir(COMD_Stop(), pObj);
  } 
  else
    RouteToVehicle("ControlLeft", pObj);
  return(1);
}

public func ControlRight(pObj) 
{
  [$TxtStop$]
  if (GetAction() ne "Wait") 
  {
    DoControlStop(pObj);
    SetComDir(COMD_Stop(), pObj);
  } 
  else
    RouteToVehicle("ControlRight", pObj);
  return(1);
}

public func ControlThrow(pObj) 
{
  [$TxtPutGet$]
  return(RouteToVehicle("ControlThrow", pObj));
}

/*public func ControlDigSingle(pObj) ...deaktiviert, weil nervt
{
  [$TxtPermanentmode$]
  DoControlAuto(pObj);
}*/

public func ContextPermanentModeTurnOn(pObj) 
{
  [$TxtPermanentModeTurnOn$|Image=ELEC|Condition=IsNotInPermanentMode]
  DoControlAuto(pObj);
}
 
public func ContextPermanentModeTurnOff(pObj) 
{
  [$TxtPermanentModeTurnOff$|Image=ELEC|Condition=IsInPermanentMode]
  DoControlAuto(pObj);
}
 
/* Nachrichten */

private func GetAutoModeString(iAutoMode)
{
  if (iAutoMode) 
    return("$TxtPermanentmodeon$");
  else
    return("$TxtPermanentmodeoff$");
}

public func IsInPermanentMode()
{
  return(AutoMode);
}
  
public func IsNotInPermanentMode()
{
  return(!AutoMode);
}
