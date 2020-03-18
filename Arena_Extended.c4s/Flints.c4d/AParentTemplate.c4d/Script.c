/*-- Neues Objekt --*/

#strict

public func Damage(int iChange, int iByPlayer) {
  if(!ObjectCall(this(),"NoShiftOwner"))
    SetOwner(iByPlayer);
  return(_inherited(iChange, iChange));
}


ChangeEvent:
  ChangeDef(Par(0));
  return(1);

Entrance:
  SetOwner(GetOwner(Par(0)),this());
  return(1);