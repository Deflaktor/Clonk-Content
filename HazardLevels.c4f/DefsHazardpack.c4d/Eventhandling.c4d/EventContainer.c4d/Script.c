#strict
#include T_1_
/* Container */

public func Pack() {
  SetActive(true);
  while(Var(0)=FindObject(0,0,0,0,0,0,0,0,NoContainer(),Var(0)))
    if(ObjectCall(Var(0),"IsEventHandler")&&GetID(Var(0))!=GetID())
	  Var(0)->Pack(this());
  return(1);
}

public func Unpack() {
  while(Var(0)=FindObject(GetID(),0,0,0,0,0,0,0,0,Var(0)))
    if(!Var(0)->IsActive()) {
      Var(0)->Pack();
    }
  SetActive(false);
  while(Var(0)=Contents()) {
    Var(0)->Unpack();
  }
  return(1);
}

protected func Execute(object pActuator) {
  Unpack();
  _inherited();
  return(1);
}

IsTriggerable:
  return(1);