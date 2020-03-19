/*--- Wachdrone ---*/
#strict
#include _CL_
// Locals
// 0 Aktueller Waypoint
// 1 Override durch Fernsteuerung
local patrolObj;
local remote;
/* Initialisierung */

protected Initialize:
  SetAction("Travel");
  return(1);
  
/* TimerCall */

Platzen:
  DoDamage(1000);
  return(1);

public func SetRemote(object obj) {
  remote = obj;
}

public func SetPatrolObject(object obj) {
  patrolObj=obj;
  if(patrolObj)
    Patrol();
}

public func GetPatrolObject() {
  return patrolObj;
}

private func Patrol() {
  var dir = GetComDir(patrolObj);
  var xOffset = 0;
  if(dir == COMD_Left)
    xOffset = 30;
  if(dir == COMD_Right)
    xOffset = -30;
  SetCommand(this(),"MoveTo",0,GetX(patrolObj)+xOffset,GetY(patrolObj)-30,0,0,1);
  AppendCommand(this(),"Call",this(),0,0,0,0,"Patrol");
}

protected Activity:
  SetAlive(1);
  // Feinde
  CheckTarget();
  // Flugrichtung
  CheckDirection();
  // In Bewegung, nichts machen
  if (SEqual(GetCommand(),"MoveTo")) return(1);
  if(patrolObj) {
    Patrol();
    return(1);
  }
  // Zum nächsten Waypoint fliegen (wenn kein Override)
  if (Not(Local(1))) MoveToNextWaypoint();
  // Override zurückzählen
  if (Local(1)) SetLocal(1,Sum(Local(1),-1));
  return(1);  

/* Flugsteuerung */

private CheckDirection:
  if (GreaterThan(GetXDir())) 
    if (Equal(GetDir(),DIR_Left()))
      SetAction("Turn",0,0,0,SetDir(DIR_Right()));
  if (LessThan(GetXDir())) 
    if (Equal(GetDir(),DIR_Right()))
      SetAction("Turn",0,0,0,SetDir(DIR_Left()));
  return(1);     

MoveToPatrolObj:
  SetXDir(0);
  SetYDir(0);
  return(1);

MoveToNextWaypoint:
  if(Local(1))
    return(1);
  // Nächsten Waypoint suchen
  if (Equal(Local(0),0)) SetVar(0,FindObject(WAY1,0,1,-1,-1));  
  if (Equal(Local(0),1)) SetVar(0,FindObject(WAY2,0,1,-1,-1));  
  if (Equal(Local(0),2)) SetVar(0,FindObject(WAY3,0,1,-1,-1));  
  if (Equal(Local(0),3)) SetVar(0,FindObject(WAY4,0,1,-1,-1)); 
  if (Equal(Local(0),4)) SetVar(0,FindObject(WAY5,0,1,-1,-1)); 
  if (Equal(Local(0),5)) SetVar(0,FindObject(WAY6,0,1,-1,-1)); 
  if (Equal(Local(0),6)) SetVar(0,FindObject(WAY7,0,1,-1,-1)); 
  if (Equal(Local(0),7)) SetVar(0,FindObject(WAY8,0,1,-1,-1)); 
  if (Equal(Local(0),8)) SetVar(0,FindObject(WAY9,0,1,-1,-1)); 
  // Kein Waypoint gefunden
  if (Not(Var(0))) return(0);
  // Kommando setzen
  SetCommand(this(),"MoveTo",Var(0),0,0,0,0,1);
  AppendCommand(this(),"Call",this(),0,0,0,0,"MoveToNextWaypoint");
  // Wegpunkt weiterzählen
  SetLocal(0,Sum(Local(0),+1));
  if (GreaterThan(Local(0),8)) SetLocal(0,0);
  return(1);


MoveToNextWaypointFailed:
  Local(0)--;
  Reset();
  // Stoppen
  SetXDir(0);
  SetYDir(0);
  return(1);

public Reset:
  SetCommand(this(),"None");
  return(1);
  
private CheckTarget:
  // Clonk suchen, Laser abfeuern
  while( Var(0)=FindObject(0, -100,-100,200,200, OCF_Prey(),0,0,NoContainer(),Var(0) ) )
    if(GetTarget(Var(0)))
      if(PathFree(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))))
        return(Fire(Var(0)));
  return(1);

private func Fire(object target) {
  var weapID = GetWeapID();
  if(weapID == LSR1) if(Random(2)) return(1);
  if(weapID == GBK2) if(Random(3)) return(1);
  var dir = GetDir();
  var xOffset = 0;
  if(dir == DIR_Left)
    xOffset = -15;
  if(dir == DIR_Right)
    xOffset = 15;
  var weap = CreateObject(weapID,xOffset,5,GetOwner());
  if(weapID==LSR1)
    ObjectCall(weap,"Launch",this(),target);
  else {
    if (GetAction() S= "Turn") return(RemoveObject(weap));
    var angle = Angle(GetX(weap),GetY(weap),GetX(target),GetY(target));
    if (angle>180&&GetDir()==DIR_Right()) return(RemoveObject(weap));
    if (angle<180&&GetDir()==DIR_Left()) return(RemoveObject(weap));
    var speed = 100;
    if(weapID==GBK2) {
      speed = 150;
    }
    var xspd = Sin(angle,speed);
    var yspd = -Cos(angle,speed);
    ObjectCall(weap,"Launch",xspd,yspd);
    SetLocal(0,xspd,weap);
    SetLocal(1,yspd,weap);
    SetR(angle,weap);
    SetLocal(2,target,weap);
    SetLocal(3,1,weap);
    if(weap->~IsMissile()) 
      Sound("Launch");
    if(weapID==GBK2) {
      Sound("SwordShot");
      SetR(angle+90,weap);
      SetDir(0,weap);
      weap->stark();
    }
  } 
  return(1);
}

private func GetWeapID() {
  if(remote) {
    if(remote->~GetDrone()==this) {
      var power = remote->~GetPower();
      if(power == 0) 
        return(LSR1);
      if(power == 1) 
        return(_HMS);
      if(power == 2) 
        return(GBK2);
    }
  }
  return(LSR1);
}

/* Punkteauswertung */

protected Damage:
  // Jeder Treffer auf eine Drone bringt Punkte
  if (Not(Equal( Par(1), GetOwner() )))
    DoScore( Par(1), Div(Par(0),2) );
  // Zerstörung
  if (LessThan(GetDamage(),60*(Global(4)+100)/100)) return(0);
  RemoveObject();
  ObjectCall(CreateObject(EXPL),"Launch",30);
  CastObjects(_DFR,3,40,0,0);
  CastObjects(_DFS,6,40,0,0);
  return(1);  

/* Fernsteuerung */

public RemoteControlAccess:
  Sound("Electric");
  CastObjects(SPK2,5,10,0,0,15);
  return(1);

public ControlUp:
  SetCommand(this(),"None");
  SetComDir(COMD_Up());
  SetLocal(1,15);
  return(1);
public ControlDown:
  SetCommand(this(),"None");
  SetComDir(COMD_Down());
  SetLocal(1,15);
  return(1);
public ControlLeft:
  SetCommand(this(),"None");
  SetComDir(COMD_Left());
  SetLocal(1,15);
  return(1);
public ControlRight:
  SetCommand(this(),"None");
  SetComDir(COMD_Right());
  SetLocal(1,15);
  return(1);

