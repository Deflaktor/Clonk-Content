#strict
#include T_1_
/* Destroyer */

local commandString, warpPlayers;

public func Copy() {
  var obj = inherited();
  obj->SetCommandMode(commandString);
  obj->SetAffectAllPlayers(warpPlayers);
  return(obj);
}

protected func TargetCompatible(object pTarget) {
  return(1);
}

protected func AlternativeComment() {
  return(commandString);
}

public func TargetActuator() {
  target=0;
  return(1);
}

protected func Execute(object pActuator) {
  var obj;
  obj = pActuator;
  if(GetTarget())
    obj = target;
  if(warpPlayers) {
    for(var i,j=GetPlayerCount(); j; ++i)
      if (GetPlayerName(i)) {
        WarpHim(GetCursor(i));
        --j;
      }
  } else {
    WarpHim(obj);
  }
  return(1);
}

private func WarpHim(object obj) {
  if(Contained(obj))
    obj->Exit();
  if(commandString)
    SetCommand(obj,commandString,0,GetX(),GetY());
  else
    SetPosition(GetX(),GetY(),obj);
}

public func SetWarpMode() {
  commandString = 0;
  return(1);
}

public func SetCommandMode(string command) {
  commandString = command;
  return(1);
}

public func SetAffectAllPlayers(bool enabled) {
  warpPlayers = enabled;
  return(1);
}

IsTriggerable:
  return(1);
