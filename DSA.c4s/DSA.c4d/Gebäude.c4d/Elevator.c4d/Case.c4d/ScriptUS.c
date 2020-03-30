/*-- Fahrstuhlkorb --*/

/* Steuerung */

public func ControlDownSingle(pObj) { [Down]          DoControlDown(pObj); return(1); }
public func ControlUp(pObj)         { [Up]            DoControlUp(pObj);   return(1); }
public func ControlLeft(pObj)       { [Stop]          DoControlStop(pObj); return(1); }
public func ControlRight(pObj)      { [Stop]          DoControlStop(pObj); return(1); }
public func ControlDigDouble(pObj)  { [Drill shaft]   DoControlDig(pObj);  return(1); }
public func ControlThrow(pObj)      { [Permanent mode]DoControlAuto(pObj); return(1); }
