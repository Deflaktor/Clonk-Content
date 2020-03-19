#strict
#include T_1_
/* Activator */

local eventNumber;

public func Copy() {
  var obj = inherited();
  obj->SetEventNumber(eventNumber);
  return(obj);
}

protected func Execute(object pActuator) {
  Call(Format("Event%d",eventNumber), pActuator);
  return(1);
}

public func SetEventNumber(int pEvent) {
  eventNumber = pEvent;
  return(eventNumber);
}

protected func TargetCompatible(object pTarget) {
  return(1);
}

public func Event0(object pActuator) {
  Message("Undefined User Event", this());
  return(1);
}

IsTriggerable:
  return(1);