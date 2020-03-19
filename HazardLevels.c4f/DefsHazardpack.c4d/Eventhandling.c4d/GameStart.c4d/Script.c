#strict
#include T_1_
/* GameStart */

local target2, target3;

public func SetTarget2(object newTarget) {
  Var(1) = newTarget;
  if(!Var(1)) {
    Var(1) = FindTarget();
    if(!Var(1))
      return(Message("No nearby compatible target found."));
  }
  if(!TargetCompatible(Var(1)))
    return(Message("Target is not compatible."));
  Sound("SpawnPointSet");
  if(target2) {
	if(ObjectCall(target2,"IsPositionMarker")) 
	  RemoveObject(target2);
  }
  target2 = Var(1);
  return(1);
}

public func ResetTarget2() {
  target2=0;
  return(1);
}


public func SetTarget3(object newTarget) {
  Var(1) = newTarget;
  if(!Var(1)) {
    Var(1) = FindTarget();
    if(!Var(1))
      return(Message("No nearby compatible target found."));
  }
  if(!TargetCompatible(Var(1)))
    return(Message("Target is not compatible."));
  Sound("SpawnPointSet");
  if(target3) {
  if(ObjectCall(target3,"IsPositionMarker")) 
    RemoveObject(target3);
  }
  target3 = Var(1);
  return(1);
}

public func ResetTarget3() {
  target3=0;
  return(1);
}

protected func Execute(object pActuator) {
  if(Contained())
    Contained()->Unpack();
  if(target)
    target->Trigger(pActuator);
  if(target2)
    target2->Trigger(pActuator);
  if(target3)
    target3->Trigger(pActuator);
  return(1);
}

IsTriggerable:
  return(1);