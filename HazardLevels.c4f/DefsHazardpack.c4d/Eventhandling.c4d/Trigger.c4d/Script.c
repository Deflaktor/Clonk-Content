#strict
#include T_1_
/* Trigger */

local dontChain, count;

protected func Initialize() {
  _inherited();
  count=1;
  return(1);
}

public func Copy() {
  var obj = inherited();
  obj->SetTriggerCount(count);
  return(obj);
}


public func SetComment(string pComment) {
  if(!dontChain) {
    if(Var(0)=FindObject(GetID(),-10,0)) Var(0)->ChainDeleteComment(DIR_Left());
    if(Var(0)=FindObject(GetID(),10,0)) Var(0)->ChainDeleteComment(DIR_Right());
  }
  return(_inherited(pComment));
}

public func ShowComment() {
  if(!dontChain) {
    if(Var(0)=FindObject(GetID(),-10,0)) Var(0)->ChainShowComment(DIR_Left());
    if(Var(0)=FindObject(GetID(),10,0)) Var(0)->ChainShowComment(DIR_Right());
  }
  return(_inherited());
}

protected func ChainDeleteComment(int dir) {
  if(dir == DIR_Left())
    if(Var(0)=FindObject(GetID(),-10,0)) Var(0)->ChainDeleteComment(DIR_Left());
  if(dir == DIR_Right())
    if(Var(0)=FindObject(GetID(),10,0)) Var(0)->ChainDeleteComment(DIR_Right());
  dontChain=1;
  SetComment();
  dontChain=0;
  return(1);
}

protected func ChainShowComment(int dir) {
  if(dir == DIR_Left())
    if(Var(0)=FindObject(GetID(),-10,0)) Var(0)->ChainShowComment(DIR_Left());
  if(dir == DIR_Right())
    if(Var(0)=FindObject(GetID(),10,0)) Var(0)->ChainShowComment(DIR_Right());
  dontChain=1;
  ShowComment();
  dontChain=0;
  return(1);
}

public func Trigger(object pActuator) {
  if(!dontChain) {
    if(Var(0)=FindObject(GetID(),-10,0)) Var(0)->ChainTrigger(pActuator, DIR_Left());
    if(Var(0)=FindObject(GetID(),10,0)) Var(0)->ChainTrigger(pActuator, DIR_Right());
  }
  count--;
  if(count<=0)
    return(_inherited(pActuator));
  return(0);
}

public func SetTriggerCount(int pCount) {
  count = pCount;
}

protected func ChainTrigger(object pActuator, int dir) {
  if(dir == DIR_Left())
    if(Var(0)=FindObject(GetID(),-10,0)) Var(0)->ChainTrigger(pActuator, DIR_Left());
  if(dir == DIR_Right())
    if(Var(0)=FindObject(GetID(),10,0)) Var(0)->ChainTrigger(pActuator, DIR_Right());
  dontChain=1;
  Trigger(pActuator);
  dontChain=0;
  return(1);
}

protected func Timer() {
  if(!_inherited())
    return(0);
  if(FindObject(GetID(),-10)||FindObject(GetID(),10))
    SetClrModulation(RGB(255,200,200));
  else
    SetClrModulation(RGB(255,255,255));
  if(EditCursor()==this()) {
    while( Var(0)=FindTarget(10,Var(0),GetID()) )
      if(PlaceNearOtherTrigger(Var(0)))
        break;
  }
  return(1);
}

private func PlaceNearOtherTrigger() {
  var other = Par(0);
  if(GetX()>GetX(other)) {
    if( Var(0)=FindObject(GetID(),-GetX()+GetX(other)+10,-GetY()+GetY(other)) )
      return(Var(0));
    SetPosition(GetX(other)+10,GetY(other));
  } else {
    if( Var(0)=FindObject(GetID(),-GetX()+GetX(other)-10,-GetY()+GetY(other)) )
      return(Var(0));
    SetPosition(GetX(other)-10,GetY(other));
  }
  return(0);
}

IsTriggerable:
  return(1);