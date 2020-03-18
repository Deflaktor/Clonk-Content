/*-- Totes Feuermonster --*/

#strict

local Unten;

/* Verwesung */

private func Decaying() {DoCon(-2);}

GetRider:
 if(SetVar(0,FindObject(0,0,0,0,0,0,"RideStill",this()))) return(Var(0));
 return(FindObject(0,0,0,0,0,0,"Ride",this()));

public func ControlDownDouble(caller)                        // Abspringen
{
  if (GetRider()){
  if(ObjectSetAction(Par(0),"Ride",this())) Message("Och...|menno...",Par(0),GetName(Par(0)));
  if (Equal(Par(0),GetRider()))   ObjectSetAction(Par(0),"Walk"); Sound("CommandFailure1");}
  ObjectSetAction(caller,"Walk");
return(1);
}
