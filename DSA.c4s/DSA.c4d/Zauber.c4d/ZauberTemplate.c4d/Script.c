/*-- Neues Objekt --*/

#strict

// Liefert zusätzliche Stärke des Zaubers zwischen 0% und 100% (und noch ein bisschen drüber max 40%)
// Par(0) ist der Zaubernde
CalcPower:
  return(Min(GetPhysical("Magic",0,Par(0))/40/GetValue(),100)+GetPhysical("Magic",0,Par(0))/5000);

// Berechnet den Zauberschaden
// Par(0) ist der Basis-Schaden
// Par(1) ist der Zusatz-Schaden berechnet durch CalcPower
CalcDamage:
  return((100+Par(1)*2)*Par(0)/100);