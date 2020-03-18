/*-- Glasofen --*/

#strict
#include BAS5
#include DOOR

/* Eingangssteuerung */

private SoundOpenDoor:
  return(Sound("GateOpen"));

private SoundCloseDoor:
  return(Sound("GateClose"));

/* Produktion */

public func IsProducerOf (object clonk, id def) {
  return (def == GLAS && IsBuilt());
}

public func HowToProduce (object clonk, id def) {
  AddCommand (clonk, "Wait", 0, 0, 0, 0, 0, 60);
  Production (clonk, def);
}

public func StartProduction(object clonk)
{
  // Arbeitsbefehl setzen
  AddCommand(clonk,"Call",this(),GLAS,0,0,0,"Production");
  return(1);
}

public func Production(object clonk, id idProduct)
{
  if (GetAction()S="Burning") return(1);
  // Kein Brennmaterial
  if (!HasFuel())
    // Der Arbeiter soll welches beschaffen
    WorkerAcquireFuel(clonk);

  // Kein Soda im Hochofen
  if (!FindContents(SODA))
    {
    // Der Arbeiter soll welches beschaffen
    AddCommand(clonk,"Call",this(),0,0,0,0,"Acquisition", 0, 3);
    AddCommand(clonk,"Put",this(),0,0,0,0,SODA);
    AddCommand(clonk,"Acquire",0,0,0,0,0,SODA,3);  
    }

  // Kein Sand im Hochofen
  if (!FindContents(SAND))
    {
    // Der Arbeiter soll welches beschaffen
    AddCommand(clonk,"Call",this(),0,0,0,0,"Acquisition", 0, 3);
    AddCommand(clonk,"Put",this(),0,0,0,0,SAND);
    AddCommand(clonk,"Acquire",0,0,0,0,0,SAND,3);  
    }

  // Fertig
  return(1);
}
  
func WorkerAcquireFuel (object clonk) {
  AddCommand (clonk, "Call", this (), 0, 0, 0, 0, "Acquisition", 0, 3);
  // Wenn Kohle da (Leider noch keine Überprüfung auf Kohleherstellendes Objekt)
  var obj = GetAvailableObject (COAL, this());
  // Oder Kohle kaufbar
  if (!obj)
    if (GetHomebaseMaterial (GetOwner (clonk), COAL))
      if (GetWealth (GetOwner (clonk)) >= GetValue (0, COAL))
        if (FindBase (GetOwner (clonk)))
          obj = 1;
  if (obj) {
    //Kohle reintun
    AddCommand(clonk,"Put",this(),0,0,0,0,COAL);
    //und vorher besorgen
    AddCommand(clonk,"Acquire",0,0,0,this(),0,COAL);
    return(1);
  }
  // ansonsten Holz verbrennen
  // ..zweites holen
  AddCommand(clonk,"Call",this(),0,0,0,0,"SupportWithWOOD", 0, 1);
  AddCommand(clonk,"Put",this(),0,0,0,0,WOOD);
  AddCommand(clonk,"Acquire",0,0,0,this(),0,WOOD);
  // Damit er es nicht nochmal holt:
  AddCommand(clonk,"Wait",0,0,0,0,0,10);
  // Erstes Holzstück holen...
  AddCommand(clonk,"Put",this(),0,0,0,0,WOOD);
  AddCommand(clonk,"Acquire",0,0,0,this(),0,WOOD);
}    

public func SupportWithWOOD() { return(1); }

public func SupportWithWOODFailed(pClonk)
{
  // Hat nicht geklappt, also mit Kohle versuchen
  AddCommand(pClonk, "Call", this(), 0, 0, 0, 0, "SupportWithCOAL", 0, 1);
  AddCommand(pClonk, "Put", this(), 0, 0, 0, 0, COAL);
  AddCommand(pClonk, "Acquire", 0, 0, 0, this(), 0, COAL);
  return(1);
}

public func SupportWithCOAL() { return(1); }

public func SupportWithCOALFailed(pClonk)
{
  // Hat auch nicht geklappt. Dann halt Ölfässer suchen...
  AddCommand(pClonk, "Call", this(), 0, 0, 0, 0, "Acquisition", 0, 3);
  AddCommand(pClonk, "Put", this(), 0, 0, 0, 0, OBRL);
  AddCommand(pClonk, "Acquire", 0, 0, 0, this(), 0, OBRL);
  return(1);
}

// --------------------------------------------------

private func HasFuel()
{
  if (ContentsCount(COAL)>0) return(1);
  if (ContentsCount(OBRL)>0) return(1);
  if (ContentsCount(WOOD)>1) return(1);
  return(0);  
}

public func Acquisition(object pWorker)
{
  // Materialbeschaffung erfolgreich
  return(1);
}

public func AcquisitionFailed(object pWorker)
{
  // Materialbeschaffung fehlgeschlagen: Meldung ausgeben
  if (!FindContents(SAND)) 
    return(Message("$TxtNoSandavailable$", pWorker));
  // Materialbeschaffung fehlgeschlagen: Meldung ausgeben
  if (!FindContents(SODA)) 
    return(Message("$TxtNoSodaavailable$", pWorker));
  Message("$TxtNeedsfueltoburn$", pWorker);
  return(1);
}

public func AcquisitionSand(object pWorker)
{
  // Materialbeschaffung erfolgreich
  return(1);
}

public func AcquisitionSandFailed(object pWorker)
{
  // Materialbeschaffung fehlgeschlagen: Meldung ausgeben
  if (!FindContents(SAND)) 
    return(Message("$TxtNoSandavailable$", pWorker));
  Message("$TxtNeedsfueltoburn$", pWorker);
  return(1);
}

/* Kontext */

public func ContextConstruction(object pCaller)
{
  [$TxtProduceglass$|Image=GLAS|Condition=IsBuilt]
  return(StartProduction(pCaller));
}

protected func IsBuilt() {
  return(GetCon() >= 100);
}

/* Steuerung */

protected func ContainedUp(object pCaller)
{
  [$TxtProduceglass$|Image=GLAS]
  return(StartProduction(pCaller));
}

protected func Collection()
{
  return(Sound("Clonk"));
}

/* Produktion */

private func Burning()
{
  // Rauch
  Smoke(+23,Random(3)-24,Random(5)+8);
  // Noch nicht fertig
  if (GetActTime()<250) return(1);
  // Fertig
  SetAction("Idle");
  // Soda suchen
  var pSoda;
  if (!(pSoda=FindContents(SODA))) return(1);
  // Sand suchen
  var pSand;
  if (!(pSand=FindContents(SAND))) return(1);
  // Soda verbrauchen
  RemoveObject(pSoda);
  // Sand verbrauchen
  RemoveObject(pSand);
  // Glas auswerfen
  SetCommand(CreateContents(GLAS), "Exit");
  // Sound
  Sound("Pshshsh");
  // Fertig
  return(1);
}

/* Inhaltsüberprüfung */  
  
private func ContentsCheck()
{
  // Warten...
  if (!ActIdle()) 
    return(1);
  // Loren ausleeren und rausschicken
  var obj;
  for(var i = 0; obj = Contents(i); i++)
    if(obj->~IsLorry())
      {
      GrabContents(obj);
      SetCommand(obj,"Exit");
      }
  // Erstes Inhaltsobjekt überprüfen
  obj = Contents(0); var id = GetID(obj);
  // Alles außer Mannschaftsmitgliedern, Rohmaterial und Loren sofort auswerfen
  if (obj)
    if ( !(    GetOCF(obj) & OCF_CrewMember()
            || obj->~IsLorry()
            || id==COAL
            || id==OBRL
            || id==WOOD
            || id==SAND 
            || id==SODA ) )
      //if(GetDefFragile(id))
        SetCommand(obj, "Exit");
      //else
      //  Exit(obj,-27,+13,0,-1); 
  // Soda prüfen
  if (!FindContents(SODA)) return(1);
  // Sand prüfen
  if (!FindContents(SAND)) return(1);
  // Holz verbrennen
  if (ContentsCount(WOOD)>1) return(BurnWood());
  // Öl verbrennen
  if (ContentsCount(OBRL)>0) return(BurnOil());
  // Kohle verbrennen
  if (!(obj=FindContents(COAL))) return(1);
  RemoveObject(obj);
  SetAction("Burning");
  return(1);
}

private func BurnWood()
{
  RemoveObject(FindContents(WOOD));
  RemoveObject(FindContents(WOOD));
  SetAction("Burning");
  return(1);
}

private func BurnOil()
{
  ChangeDef(BARL,FindContents(OBRL));
  SetAction("Burning");
  return(1);
}

public GetResearchBase:
  return(SODA);