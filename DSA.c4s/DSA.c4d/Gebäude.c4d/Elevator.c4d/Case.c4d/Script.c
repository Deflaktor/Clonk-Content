/*-- Fahrstuhlkorb --*/

#strict

// Local 8: Obergrenze
// Local 9: Untergrenze

local AutoMode;       // Dauerbetrieb
local AutoMoveDir;    // Dauerbetrieb Richtung
local RangeTop;       // Obergrenze
local RangeBottom;    // Untergrenze

local oElev;          // Das Fahrstuhl-Objekt

/* TimerCall */

protected func Activity()
{
  // Legacy
  if (Local(8) && !RangeTop) ImportSettings();
  // Fahrstuhl zerstört
  if (!Elevator() || OnFire(Elevator())) { SetAction("Idle"); Incinerate(); return(); }
  // Lore fassen
  GrabLorry();
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
  if (!(oClnk = FindObject(0, -30, RangeTop - GetY(), 60, 6000, OCF_CrewMember(), 0, 0, NoContainer()))) return(0);
  if (GetComDir(oClnk) != COMD_Stop()) return(0);
  if (GetAction(oClnk) ne "Walk" && GetAction(oClnk) ne "Push" && GetAction(oClnk) ne "Scale" && GetAction(oClnk) ne "Hangle") return(0);
  // Nicht wenn der Clonk zu nah ist
  if (Abs(GetY(oClnk) - GetY()) <= 15) return(0);
  // Nicht bei verfeindeten Clonks
  if (Hostile(GetController(oClnk), GetOwner())) return(0);
  // Nur wenn der Weg frei ist
  if (GetY(oClnk) < GetY()) if (!PathFree(GetX(), GetY(), GetX(), GetY(oClnk))) return(0);
  if (GetY(oClnk) > GetY()) if (!PathFree(GetX(), GetY()+16, GetX(), GetY(oClnk))) return(0);
  // Zielposition setzen und starten
  SetMoveTo(GetY(oClnk));
  return(1);              
}

private func GrabLorry()
{
  if (GetAction() ne "Wait") return(0);
  var oLory;
  if (!(oLory = FindObject(LORY, -7, -7, 15, 15))) return(0);
  if (GetX(oLory) == GetX() && GetY(oLory) == GetY() + 1) return(0);
  SetPosition( GetX(), GetY() + 1, oLory);
  SetR(0, oLory);
  SetRDir(0, oLory); SetXDir(0, oLory); SetYDir(0, oLory);
  return(1);
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
  // Dauerbetrieb: selbständig losfahren
  if (AutoMode == 1)
    SelfMovement();
  return(1);
}

private func SelfMovement()
{
  // Selbständig rauf- bzw. runterfahren
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
    if (Inside(iTx, GetX()-15, GetX()+15))
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
  if (!Elevator()) return(0);
  if (NoEnergy()) return(0);
  Sound("Click");
  if (Hostile(GetController(pObj), GetOwner())) return(0);
  SetMoveTo(Sum(LandscapeHeight(),-12));
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
  if (!Elevator()) return(0);
  Sound("Click");
  if (Hostile(GetController(pObj), GetOwner())) return(0);
  AutoMode = !AutoMode;
  Message(GetAutoModeString(AutoMode), this());
}        

private func GetAutoModeString(iAutoMode)
{
  if(iAutoMode) 
    return("Permanent mode on");
  else
    return("Permanent mode off");
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
  return (FindObject(0, -12,-13,24,20, OCF_CrewMember(),0,0,NoContainer()));
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
  SetTransferZone(-12, GetY(oElev) - GetY(), 24, RangeBottom - GetY(oElev) + 12);
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

  // Fahrstuhl fährt: warten
  if (GetAction() ne "Wait")
    return(1);

  // Fahrstuhl noch nicht beim Clonk: warten
  if (!Inside(GetY() - GetY(pObj), -15, +15))
    return(1);

  // Fahrstuhl nur in der Mitte anfassen
  if (!Inside(GetX() - GetX(pObj), -5, +5))
    return(AddCommand(pObj,"MoveTo",this()));

  // Fahrstuhl anfassen
  if (GetAction(pObj) ne "Push" || GetActionTarget(0, pObj) != this())
    return(AddCommand(pObj,"Grab",this()));
  
  // Fahrstuhl zur Zielposition steuern
  return(SetMoveTo(iTy));
}


/* Zerstörung: Reduzieren des Fahrstuhls für Wiederaufbau/Reparatur */

func Destruction() { if(Elevator()) Elevator()->RemoveCase(); }

/* Bei Laden von alten Spielständen: Locals zurückkopieren */

func ImportSettings()
{
  AutoMode = Local(0);
  AutoMoveDir = Local(7);
  RangeTop = Local(8);
  RangeBottom = Local(9);
}