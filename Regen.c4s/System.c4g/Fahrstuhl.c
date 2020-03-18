/*-- Fahrstuhl Korb --*/

#strict
#appendto ELEC

private func NoEnergy()
{
  var elev = Elevator();
  if (Local(0,elev)) {
    Local(0,elev)--;
    return(0);
  }
  return(_inherited());
}



protected func Riding() 
{
  var elev = Elevator();
  if (!elev) return Halt();
  // Energieverbrauch
  if (ObjectCount(ENRG)&&!Local(0,elev))
    if (EnergyCheck(12500, elev))
      DoEnergy(-12500, elev, true);
    else
      Halt();
  if(Local(0,elev)) {
    EnergyCheck(0, elev);
	Local(0,elev)--;
  }
}

private func Drilling()
{
  // Steuermann verloren? Suche schiebenden Clonk selbst wenn er ein Fahrzeug im Fahrstuhlkorb schiebt (->Lore)
  var elev = Elevator();
  if (!elev) return Halt();
  if (!FindObject2(Find_InRect(-12,-12,24,24), Find_Action("Push")))
    return Halt();
  // Energieverbrauch
  if (ObjectCount(ENRG)&&!Local(0,elev))
    if (EnergyCheck(10000, elev))
      DoEnergy(-10000, elev, true);
    else
      Halt();
  if(Local(0,elev)) {
    EnergyCheck(0, elev);
	Local(0,elev)--;
  }
  return(1);
}
