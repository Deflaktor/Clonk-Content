#strict
/*-- Abstract EventHandling Superobject --*/

local active, target, wait, timeToTrigger, bm, actuator, unpackedX, unpackedY, comment;

private func Initialize() {
  SetAction("Showing");
  SetActive(1);
  timeToTrigger = -1;
  return(1);
}

public func Copy() {
  var obj = CreateObject(GetID(), 0, 0, -1);
  obj->SetActive(active);
  obj->SetTarget(target, true);
  obj->SetWait(wait);
  obj->SetComment(comment);
  return(obj);
}

public func SetComment(string pComment) {
  comment = pComment;
  return(1);
}

protected func ShowComment() {
  if(comment)
    Message(comment, this());
  else if(AlternativeComment()) 
    Message(AlternativeComment(), this());
  return(1);
}

protected func AlternativeComment() {
  return(0);
}

public func SetAllowPacking(bool pAllow) {
  if(Contained())
    return(0);
  if(!pAllow) {
    unpackedX = -1;
	unpackedY = -1;
  } else {
    unpackedX = 0;
	unpackedY = 0;
  }
  return(1);
}

public func Pack(object pObject) {
  if(!pObject)
    return(Message("Only use this function for the event container"));
  if(unpackedX==-1&&unpackedY==-1)
    return(1);
  unpackedX = GetX();
  unpackedY = GetY();
  Enter(pObject);
  return(1);
}

public func Unpack() {
  if((!unpackedX&&!unpackedY)||(unpackedX==-1&&unpackedY==-1))
    return(Message("Only use this function for the event container"));
  Exit();
  SetPosition(unpackedX, unpackedY);
  return(1);
}

public func SetWait(int timeInFrames) {
  wait = timeInFrames;
  return(wait);
}

protected func TargetCompatible(object pTarget) {
  return(ObjectCall(pTarget,"IsTriggerable"));
}

public func SetTarget(object newTarget, bool direct) {
  Var(1) = newTarget;
  if(!Var(1)&&!direct) {
    Var(1) = FindTarget();
    if(!Var(1))
      return(Message("No nearby compatible target found."));
  }
  if(!TargetCompatible(Var(1))&&!direct)
    return(Message("Target is not compatible."));
  Sound("SpawnPointSet");
  if(target) {
    SetObjectBlitMode(bm, target);
	if(ObjectCall(target,"IsPositionMarker")) 
	  RemoveObject(target);
  }
  target = Var(1);
  bm = GetObjectBlitMode(target);
  return(1);
}

protected func Destruction() {
  if(target) {
    SetObjectBlitMode(bm, target);
  }
  return(1);
}

public func ResetTarget() {
  target=0;
  return(1);
}

public func GetTarget() {
  return(target);
}

protected func FindTarget(int distance, object skipTarget, id def) {
  Var(0) = skipTarget;
  if(distance == 0)
    distance = 30;
  while(Var(0) = FindObject(def,0,0,-1,-1,0,0,0,0,Var(0)))
    if(TargetCompatible(Var(0)))
      if(Distance( GetX(),GetY(),GetX(Var(0)),GetY(Var(0)) ) < distance)
        return(Var(0));
  return(0);
}

public func Trigger(object pActuator) {
  if(!active)
    return(0);
  actuator = pActuator;
  if(!actuator)
    actuator = this();
  if(wait==0) {
    if(GetAction()S="Showing")
      CreateObject(T01_)->Trigger();
    Execute(actuator);
    return(1);
  }
  timeToTrigger = wait;
  if(GetAction()S="Showing")
    CreateObject(T01_)->Trigger(wait);
  return(1);
}
  
protected func CheckExecute() {
  if(timeToTrigger<0)
    return(1);
  timeToTrigger--;
  if(timeToTrigger==-1)
    Execute(actuator);
  return(1);
}

protected func Execute(object pActuator) {
  if(target)
    target->Trigger(pActuator);
  return(1);
}
  
public func Show() {
  SetAction("Showing");
  return(1);
}

public func Hide() {
  SetAction("Hiding");
  SetCommand(this(), "None");
  return(1);
}

protected func IsActive() {
  return(active);
}

public func SetActive(bool pActive) {
  active=pActive;
  return(active);
}

public func DebugOn() {
  Show();
  while(Var(0)=FindObject(0,0,0,0,0,0,0,0,0,Var(0))) {
    if(ObjectCall(Var(0),"IsPositionMarker")) ObjectCall(Var(0), "Show");
	if(ObjectCall(Var(0),"IsEventHandler")) ObjectCall(Var(0), "Show");
    if(ObjectCall(Var(0),"IsWaypoint")) ObjectSetAction(Var(0),"ShowWaypoint");
  }
  return(1);
}

public func DebugOff() {
  Hide();
  while(Var(0)=FindObject(0,0,0,0,0,0,0,0,0,Var(0))) {
    if(ObjectCall(Var(0),"IsPositionMarker")) ObjectCall(Var(0), "Hide");
    if(ObjectCall(Var(0),"IsEventHandler")) ObjectCall(Var(0), "Hide");
    if(ObjectCall(Var(0),"IsWaypoint")) ObjectSetAction(Var(0),"Waypoint");
  }
  return(1);
}

protected func Timer() {
  CheckExecute();
  if(GetAction()S="Hiding")
    return(0);
  if(EditCursor()==this())
    ShowComment();
  else Message("", this());
  if(target&&!Contained()) {
    // Only show target when more than 20 pixels away to avoid blinking of the Command
    if(Distance(GetX(),GetY(),GetX(target),GetY(target))>20)
      SetCommand(this(), "MoveTo", 0, GetX(target), GetY(target), 0, true);
    if(EditCursor()==this()) {
      SetObjectBlitMode(1, target);
    } else {
      SetObjectBlitMode(bm, target);
    }
  } else {
    SetCommand(this(), "None");
  }
  return(1);
}

IsTriggerable:
  return(0);

IsEventHandler:
  return(1);
  
IsPositionMarker:
  return(0);
