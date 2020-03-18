/*-- Explosionsdruckwelle --*/

#strict
local alpha; // Durchsichtigkeit
local explo_obj; // Explosionssteuerungsobjekt

/* Aktivierung */

public func Activate()
  {
  explo_obj = Par(0);
  SetCon(1);
  SetAction("Blow");
  return(1);
  }

/* Aufblähen */

private func BlowExec()
  {
  if(alpha==255) return(RemoveObject());
  if(GetCon()<=100)
    {
    DoCon(+4);
    SetPosition(GetX(explo_obj),GetY(explo_obj));
    }
  // Langsam durchsichtig werden
  SetClrModulation(RGBa(255,255,255,alpha));
  alpha=BoundBy(alpha+10,0,255);
  return(1);
  }