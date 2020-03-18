/*-- Erde-Sand Konverter --*/

#strict
#include BAS3
#include CXEC

/* Produktion */

public func IsProducerOf (object clonk, id def) {
  if (def != SAND) return (0);
  if (!IsBuilt ()) return (0);
  if (NeedsEnergy ())
    if (FindSuppliedObjectCloseTo (clonk)) return (0);
//  if (!FindWorkTree (clonk)) return (0);
  return(1);
}

private func FindSuppliedObjectCloseTo (object obj, id def) {
  var obj2;
  if (!def) def = GetID ();
  while (obj2 = FindObject (def, (GetX (obj) - 1000) - GetX (), (GetY (obj) - 500) - GetY (), 2000, 1000,
    OCF_Fullcon (), 0, 0, 0, obj2))
      if (FindObject (PWRL, 0,0,0,0, 0,"Connect",obj2))
        return(obj2);
  return(0);
}

protected func IsBuilt() {
  return(GetCon() >= 100);
}

public func HowToProduce (object clonk, id def) {
  //Eventuell erst versorgen
  if (NeedsEnergy ())
  {
    AddCommand (clonk, "Call", this (), SAND, 0, 0, 0, "HowToProduce");
    AddCommand (clonk, "Energy", this ());
    return (1);
  }
  AddCommand (clonk, "Wait", 0, 0, 0, 0, 0, 60);
  Production (clonk, def);
}

public func StartProduction(object clonk)
{
  // Arbeitsbefehl setzen
  AddCommand(clonk,"Call",this(),SAND,0,0,0,"Production");
  return(1);
}

public func Production(object clonk, id idProduct)
{
  // Nicht genug Erde
  if (Local(0)+Local(1)<5) {
    // Der Arbeiter soll welches beschaffen
    AddCommand(clonk,"Call",this(),0,0,0,0,"Acquisition", 0, 3);
    var i;
    i=5-Local(0)+Local(1);
    while(i) {
      AddCommand(clonk,"Put",this(),0,0,0,0,ERTH);
      AddCommand(clonk,"Acquire",0,0,0,0,0,ERTH,3);
      i--;
    }
  }
  // Fertig
  return(1);
}

public func Acquisition(object pWorker)
{
  // Materialbeschaffung erfolgreich
  return(1);
}

public func AcquisitionFailed(object pWorker)
{
  // Materialbeschaffung fehlgeschlagen: Meldung ausgeben
  return(Message(Format("$TxtNoEarthavailable$", 5-Local(0)+Local(1)), pWorker));
}

/* Kontext */

public func ContextConstruction(object pCaller)
{
  [$Txtproducesand$|Image=SAND|Condition=IsBuilt]
  return(StartProduction(pCaller));
}

/* Steuerung */

protected func ControlUp(object pCaller)
{
  [$Txtproducesand$|Image=SAND]
  return(StartProduction(pCaller));
}

RejectCollect:
  if(Par(0)==ERTH)
    return(0);
  return(1);

Collection:
  SetLocal(1,Local(1)+1);
  if(ActIdle())
    SetAction("CreateI");
  RemoveObject(Par(0));
  return(1);

TimeChecker:
 if (LessThan(GetActTime(),Min(Local(1),5)*200)) return(1);
   SetAction("CreateIII");
 return(1);

CreateSand:
 SetAction("Idle");
 SetLocal(0,Local(0)+Local(1));
 SetLocal(1,Max(0,Local(1)-5));
 if (Local(0)<5)
   return(1);
 CreateContents(SAND);
 SetLocal(0,Local(0)-5);
 return(1);

public GetResearchBase:
 return(ERTH);