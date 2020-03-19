#strict
#include T_1_
/* Destroyer */

local mode, explodeStrength, deleteTarget;

protected func TargetCompatible(object pTarget) {
  return(1);
}

private func Initialize() {
  _inherited();
  SetDeleteMode();
  return(1);
}

public func Copy() {
  var obj = inherited();
  if(mode==0)
    obj->SetExplodeMode(explodeStrength, deleteTarget);
  if(mode==1)
    obj->SetDamageMode(explodeStrength);
  if(mode==2)
    obj->SetBlastMode(explodeStrength);
  return(obj);
}

protected func Execute(object pActuator) {
  var targetActuator = 0;
  if(!target)
    targetActuator = 1;
  if(targetActuator)
    target = pActuator;
  var obj;
  if(GetTarget()) {
    if(GetID(GetTarget()) == TS1_)
	  obj = GetTarget()->GetLastSpawned();
	else
	  obj = GetTarget();
  } else {
    obj = pActuator;
  }  
  
  if(mode == 0) {
    var x = GetX(obj)-GetX();
	var y = GetY(obj)-GetY();
    if(deleteTarget)
	  RemoveObject(obj);
	if(explodeStrength>0)
      CreateObject(EXPL, x, y)->Launch(explodeStrength);
  }
  if(mode == 1) {
    DoDamage(explodeStrength,obj);
    DoEnergy(-explodeStrength,obj);
  }
  if(mode == 2) {
    BlastObjects(GetX(obj),GetY(obj),explodeStrength);
  }
  return(1);
}
  
public func PlaceMarker() {
  var marker = CreateObject(TP1_,0,10);
  SetTarget(marker);
}

public func SetDeleteMode() {
  mode = 0;
  explodeStrength = 0;
  deleteTarget = true;
  SetClrModulation(RGB(255,255,255));
  return(1);
}
  
public func SetExplodeMode(int strength, bool delete) {
  mode = 0;
  explodeStrength = strength;
  deleteTarget = delete;
  if(explodeStrength == 0)
    explodeStrength = 20;
  SetClrModulation(RGB(255,200,200));
  return(1);
}

public func SetDamageMode(int strength) {
  mode = 1;
  explodeStrength = strength;
  if(explodeStrength == 0)
    explodeStrength = 20;
  SetClrModulation(RGB(200,255,200));
  return(1);
}

public func SetBlastMode(int strength) {
  mode = 2;
  explodeStrength = strength;
  if(explodeStrength == 0)
    explodeStrength = 20;
  SetClrModulation(RGB(200,228,242));
  return(1);
}

IsTriggerable:
  return(1);
