#strict
#include T_1_
/* Viewer */

local blink, viewTime, countDown, viewID;
static numberTriggeredViewers;

private func Initialize() {
  _inherited();
  countDown = -1;
  blink = true;
  return(1);
}

public func Copy() {
  var obj = inherited();
  obj->SetRandomViewTarget(viewID);
  obj->SetBlink(blink);
  obj->SetViewTime(viewTime);
  return(obj);
}

public func Trigger(object pActuator) {
  numberTriggeredViewers++;
  return(_inherited(pActuator));
}

public func SetRandomViewTarget(id pViewID) {
  viewID = pViewID;
}

protected func Execute(object pActuator) {
  if(viewTime==0) {
    numberTriggeredViewers--;
    if(numberTriggeredViewers)
      return(1);
    for(var i,j=GetPlayerCount(); j; ++i)
      if (GetPlayerName(i)) {
        SetPlrView(i, GetTarget());
        --j;
      }
    if(blink) SetObjectBlitMode(1, target);
    return(1);
  }
  if(viewID) 
    if(Var(0)=FindObject(viewID))
	  target=Var(0);
  View();
  countDown = viewTime;
  return(1);
}

private func View() {
  for(var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i)) {
      var k=GetCrewCount(i); while (k--) {
        ObjectCall(GetCrew(i,k), "SetEnabled", 0);
        SetComDir(COMD_None(), GetCrew(i,k));
        SetCommand(GetCrew(i,k), "");
      }
      SetPlrView(i, GetTarget());
      --j;
    }
  return(1);
}

private func ResetView() {
  numberTriggeredViewers--;
  if(numberTriggeredViewers) {
    if(blink)
      SetObjectBlitMode(bm, target);
    return(1);
  }
  for(var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i)) {
      var k=GetCrewCount(i); while (k--) {
        ObjectCall(GetCrew(i,k), "SetEnabled", 1);
      }
      SetPlrView(i, GetCrew(i,0));
      --j;
    }
  if(blink)
    SetObjectBlitMode(bm, target);
  return(1);
}

public func SetBlink(bool pBlink) {
  blink=pBlink;
  return(blink);
}

public func SetViewTime(int pTime) {
  viewTime = pTime;
  return(viewTime);
}

protected func Timer() {
  _inherited();
  if(countDown<0)
    return(1);
  countDown--;
  if(countDown==-1)
    return(ResetView());
  if(blink) {
    if(countDown % 2 == 0)
      SetObjectBlitMode(1, target);
    else
      SetObjectBlitMode(bm, target);
  }
  return(1);
}

protected func TargetCompatible(object pTarget) {
  return(1);
}

IsTriggerable:
  return(1);