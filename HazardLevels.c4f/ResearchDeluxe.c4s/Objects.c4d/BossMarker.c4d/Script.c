#strict
#include T_1_
/* BossMarker */
local triggered, count;

protected func TargetCompatible(object pTarget) {
  return(1);
}

public func ResetTarget() {
  target=0;
  SetClrModulation(RGB(255,255,255));
  return(1);
}

public func SetCount(int pCount) {
  count = pCount;
}

public func SetTarget(object newTarget) {
  Var(0)=_inherited(newTarget);
  SetClrModulation(RGB(200,255,255));
  return(Var(0));
}

protected func Execute(object pActuator) {
  Explode(100,CreateObject(GetID()));
  triggered=2;
  // CastPXS("Metal", 6000, 1);
  return(1);
}

protected func Timer() {
  _inherited();
  if(triggered) {
    ShakeFree(GetX(),GetY(),130);
	triggered--;
  }
  return(0);
}

IsTriggerable:
  return(1);
 