#strict
#include T_1_
/* PositionMarker */

local respawnPoint, addRespawnPoint;


protected func TargetCompatible(object pTarget) {
  return(GetID()==GetID(pTarget));
}

public func PlaceMarker() {
  var marker = CreateObject(GetID(),0,10);
  if(GetTarget()) {
    marker->SetTarget(GetTarget());
  } else {
    marker->SetTarget(this());
  }
}

public func ResetTarget() {
  target=0;
  SetClrModulation(RGB(255,255,255));
  return(1);
}

public func SetTarget(object newTarget) {
  Var(0)=_inherited(newTarget);
  SetClrModulation(RGB(32,255,255));
  return(Var(0));
}

protected func Execute(object pActuator) {
  if(!addRespawnPoint)
    while(Var(0)=FindObject(GetID(),0,0,0,0,0,0,0,0,Var(0)))
      Var(0)->SetRespawnPoint(false);
  while(Var(1)=FindObject(GetID(),0,0,0,0,0,0,0,0,Var(1)) )
    if(Var(1)->GetTarget()==this()) {
	  Var(1)->SetRespawnPoint(true);
	}
  SetRespawnPoint(true);
  return(1);
}

public func SetRespawnPoint(bool pRespawnPoint) {
  respawnPoint = pRespawnPoint;
  return(respawnPoint);
}

public func AddRespawnPoint(bool pAddRespawnPoint) {
  addRespawnPoint = pAddRespawnPoint;
  return(addRespawnPoint);
}

IsRespawnPoint:
  return(respawnPoint);

IsTriggerable:
  return(1);
 
IsPositionMarker:
  return(1);