#strict
#include T_1_
/* Activator */

local activate;

private func Initialize() {
  _inherited();
  activate = true;
  return(1);
}

public func Copy() {
  var obj = inherited();
  obj->SetActivate(activate);
  return(obj);
}

protected func Execute(object pActuator) {
  if(target)
    target->SetActive(activate);
  return(1);
}

public func SetActivate(bool pActivate) {
  activate = pActivate;
  return(activate);
}

protected func TargetCompatible(object pTarget) {
  return(ObjectCall(pTarget,"IsEventHandler"));
}

IsTriggerable:
  return(1);