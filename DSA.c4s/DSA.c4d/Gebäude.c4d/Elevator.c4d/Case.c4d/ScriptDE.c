/*-- Fahrstuhlkorb --*/

/* Steuerung */

public func ControlDownSingle(pObj) { [Abw�rts]       DoControlDown(pObj); return(1); }
public func ControlUp(pObj)         { [Aufw�rts]      DoControlUp(pObj);   return(1); }
public func ControlLeft(pObj)       { [Anhalten]      DoControlStop(pObj); return(1); }
public func ControlRight(pObj)      { [Anhalten]      DoControlStop(pObj); return(1); }
public func ControlDigDouble(pObj)  { [Schachbohrung] DoControlDig(pObj);  return(1); }
public func ControlThrow(pObj)      { [Dauerbetrieb]  DoControlAuto(pObj); return(1); }

/* Nachrichten */

private func GetAutoModeString(iAutoMode)
{
  if(iAutoMode) 
    return("Dauerbetrieb eingeschaltet");
  else
    return("Dauerbetrieb ausgeschaltet");
}
