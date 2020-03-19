#strict
#include T_1_
/* Conditional */
local triggerOnce, conditionNumber, negated;

public func Copy() {
  var obj = inherited();
  obj->SetTriggerOnce(triggerOnce);
  obj->SetConditionNumber(conditionNumber);
  obj->SetConditionNegated(negated);
  return(obj);
}

public func SetTriggerOnce(bool pTriggerOnlyOnce) {
  triggerOnce=pTriggerOnlyOnce;
  return(triggerOnce);
}

public func SetConditionNumber(int pCondition) {
  conditionNumber = pCondition;
  return(1);
}

public func SetConditionNegated(bool pNegated) {
  negated = pNegated;
  return(negated);
}

protected func Timer() {
  _inherited();
  if(!IsActive()||Contained())
    return(1);
  if(GetTarget()) {
    Var(0)=Call(Format("Condition%d",conditionNumber));
	if(conditionNumber==0)
	  return(0);
	if((Var(0)&&!negated)||(!Var(0)&&negated))
	  return(TriggerIt(actuator));
  }
  return(0);
}

private func TriggerIt(object pActuator) {
  // Nearest clonk from this conditional is actuator
  if(!pActuator) pActuator = FindObject(0,0,0,-1,-1,OCF_CrewMember());
  Trigger(pActuator);
  if(triggerOnce)
    SetActive(0);
  return(1);
}

public func Condition0() {
  Message("Undefined User Condition", this());
  actuator=0;
  return(0);
}
