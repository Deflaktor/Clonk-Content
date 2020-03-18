/*-- Hochofen --*/

#strict

#include BAS8
#include DOOR

/* Produktion */

public func IsProducerOf (object clonk, id def) {
  return (def == SPHR && IsBuilt());
}

public func HowToProduce (object clonk, id def) {
  AddCommand (clonk, "Wait", 0, 0, 0, 0, 0, 60);
  Production (clonk, def);
}

public func StartProduction(object clonk)
{
  // Arbeitsbefehl setzen
  AddCommand(clonk,"Call",this(),SPHR,0,0,0,"Production");
  return(1);
}

public func Production(object clonk, id idProduct)
{
  if (GetAction()S="Burning") return(1);
  // Kein Brennmaterial
  if (!HasFuel())
    // Der Arbeiter soll welches beschaffen
    WorkerAcquireFuel(clonk);

  // Kein Erz im Hochofen
  if (!FindContents(LBRL))
    {
    // Der Arbeiter soll welches beschaffen
    AddCommand(clonk,"Call",this(),0,0,0,0,"Acquisition", 0, 3);
    AddCommand(clonk,"Put",this(),0,0,0,0,LBRL);
    AddCommand(clonk,"Acquire",0,0,0,0,0,LBRL,3);  
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
  //AddCommand(clonk,"Call",this(),0,0,0,0,"SupportWithWOOD", 0, 1);
  //AddCommand(clonk,"Put",this(),0,0,0,0,WOOD);
  //AddCommand(clonk,"Acquire",0,0,0,this(),0,WOOD);
  // Damit er es nicht nochmal holt:
  //AddCommand(clonk,"Wait",0,0,0,0,0,10);
  // Erstes Holzstück holen...
  //AddCommand(clonk,"Put",this(),0,0,0,0,WOOD);
  //AddCommand(clonk,"Acquire",0,0,0,this(),0,WOOD);
}    
/*
public func SupportWithWOOD() { return(1); }

public func SupportWithWOODFailed(pClonk)
{
  // Hat nicht geklappt, also mit Kohle versuchen
  AddCommand(pClonk, "Call", this(), 0, 0, 0, 0, "SupportWithCOAL", 0, 1);
  AddCommand(pClonk, "Put", this(), 0, 0, 0, 0, COAL);
  AddCommand(pClonk, "Acquire", 0, 0, 0, this(), 0, COAL);
  return(1);
}*/
/*
public func SupportWithCOAL() { return(1); }

public func SupportWithCOALFailed(pClonk)
{
  // Hat auch nicht geklappt. Dann halt Ölfässer suchen...
  AddCommand(pClonk, "Call", this(), 0, 0, 0, 0, "Acquisition", 0, 3);
  AddCommand(pClonk, "Put", this(), 0, 0, 0, 0, OBRL);
  AddCommand(pClonk, "Acquire", 0, 0, 0, this(), 0, OBRL);
  return(1);
}
*/
// --------------------------------------------------

private func HasFuel()
{
  if (ContentsCount(COAL)>0) return(1);
  //if (ContentsCount(OBRL)>0) return(1);
  //if (ContentsCount(WOOD)>1) return(1);
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
  if (!FindContents(LBRL)) 
    return(Message("$TxtNoLavabarrelavailable$", pWorker));
  Message("$TxtNeedsfueltoburn$", pWorker);
  return(1);
}

/* Kontext */

public func ContextConstruction(object pCaller)
{
  [$Txtproducesulphur$|Image=SPHR|Condition=IsBuilt]
  return(StartProduction(pCaller));
}

protected func IsBuilt() {
  return(GetCon() >= 100);
}

/* Steuerung */

protected func ContainedUp(object pCaller)
{
  [$Txtproducesulphur$|Image=SPHR]
  return(StartProduction(pCaller));
}

/* Eingangssteuerung */

private func SoundOpenDoor()
{
  return(Sound("GateOpen"));
}

private func SoundCloseDoor()
{
  return(Sound("GateClose"));
}

protected func Collection()
{
  return(Sound("Clonk"));
}

/* Produktion */

private func Burning()
{
  // Rauch
  var i=0;
  while(i--)
    Smoke(-20,Random(3)-52,Random(5)+20);
  CastObjectsX(_PRK,1,50+Random(10),-18,-52,270,30);
  // Noch nicht fertig
  if (GetActTime()<500) return(1);
  // Fertig
  SetAction("Idle");
  // Erz suchen
  var pOre;
  if (!(pOre=FindContents(LBRL))) return(1);
  // Erz verbrauchen
  RemoveObject(pOre);
  // Metall auswerfen
  SetCommand(CreateContents(SPHR), "Exit");
  CreateContents(BARL);
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
           // || id==OBRL
           // || id==WOOD
            || id==LBRL
            || id==BARL ) )
        SetCommand(obj, "Exit");
  // Erz prüfen
  if (!FindContents(LBRL)) return(1);
  // Holz verbrennen
  //if (ContentsCount(WOOD)>1) return(BurnWood());
  // Öl verbrennen
  //if (ContentsCount(OBRL)>0) return(BurnOil());
  // Kohle verbrennen
  if (!(obj=FindContents(COAL))) return(1);
  RemoveObject(obj);
  SetAction("Burning");
  return(1);
}
/*
private func BurnWood()
{
  RemoveObject(FindContents(WOOD));
  RemoveObject(FindContents(WOOD));
  SetAction("Burning");
  return(1);
}*/
/*
private func BurnOil()
{
  ChangeDef(BARL,FindContents(OBRL));
  SetAction("Burning");
  return(1);
}
*/

public GetResearchBase: return(COAL);  
