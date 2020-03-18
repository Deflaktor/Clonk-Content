/*-- Zerlegen --*/

#strict
#appendto DMNS
#appendto DFMN
#appendto DWPF

/* Zerlegen */
local meatCount, processed;

public func Init() {
  meatCount=4;
  if(GetID()==DWPF)
	meatCount=1;
  if(GetAction()=="Decay")
    meatCount=0;
}

public func CalcValue() {
  if(GetAction() == "Decay") return(0);
  if(!meatCount) Init(); 
  return(meatCount*4);
}

public func IsBeingProcessed() {
  return(processed);
}

public func SetBeingProcessed(bool pProcessed) {
  processed=pProcessed;
  return(1);
}

public func Activate(pClonk) {
  [Ausschlachten|Image=KNF1|Condition=IsNotDecaying]
  Decompose(pClonk);
  return();
}

public func ControlDigDouble(pClonk) {
  [Ausschlachten|Image=KNF1|Condition=IsNotDecaying]
  Decompose(pClonk);
  return();
}

private func Decompose(pClonk) {
  if(!meatCount) {
    Init();
  }
  if(GetAction() eq "Decay") return();
  if(IsBeingProcessed()) return();
  // Der Clonk soll dieses Objekt zerlegen
  AddEffect("IntDecompose",pClonk,1,1,0,GetID(),this());
}

public func IsNotDecaying() {
  return(GetAction() ne "Decay");
}

/* Wird zerlegt Komponente für Komponente */
public func Embowel(object pBy) {
  // In Bestandteile zerfallen
  if(!meatCount) return(0);
  meatCount--;
  if(!meatCount) SetAction("Decay");
  
  var id = MEAT;
  if(meatCount==3)
    id = DRTO;
  var owner = -1;
  if(pBy) owner = GetOwner(pBy);
  var obj = CreateObject(id,0,0,owner);
  SetR(Random(360),obj);
  SetXDir(RandomX(-3,3),obj);
  SetYDir(RandomX(-3,3),obj);
  SetRDir(10+Random(21),obj);
  return(obj);
}

func GetDecomposeTime() {
  return(150);
}

func FxIntDecomposeStart(object pClonk, int iNumber, int iTemp, object pTarget) {
  var szAct;
  EffectVar(0,pClonk,iNumber) = pTarget;
  EffectVar(1,pClonk,iNumber) = 0;
  pTarget->SetBeingProcessed(true);
  if(Contained(pTarget)) {
    if(GetDir(Contained(pTarget))==DIR_Right())
      Contained(pTarget)->Exit(pTarget,10,GetDefBottom(Contained(pTarget))-GetY(Contained(pTarget)));
	else
	  Contained(pTarget)->Exit(pTarget,-10,GetDefBottom(Contained(pTarget))-GetY(Contained(pTarget)));
  }
  // Process vorhanden? toll. Nicht vorhanden? nich so toll.
  // ...aber möglich!! :)
  if(GetActMapVal("Name","Process",GetID(pClonk)))
    szAct = "Process";
  else
    szAct = "FlatUp";
  pClonk->SetAction(szAct);
  EffectVar(2,pClonk,iNumber) = szAct;
}

func FxIntDecomposeTimer(object pClonk, int iNumber, int iEffectTime) {
  var pTarget = EffectVar(0,pClonk,iNumber),
      iTime = EffectVar(1,pClonk,iNumber)++,
      szAction = EffectVar(2,pClonk,iNumber);
	 
  // Objekt weg
  if( !pTarget || pClonk->ObjectDistance(pTarget)>20 )
    return(-1,pClonk->SetAction("KneelUp"));

  if( pTarget->GetAction() eq "Decay" )
    return(-1,pClonk->SetAction("KneelUp"));

  // Zeit abgelaufen
  if(iTime>=GetDecomposeTime()) {
    EffectVar(1,pClonk,iNumber) = 0;
	
	if(!pTarget->Embowel(pClonk))
	  return(-1,pClonk->SetAction("KneelUp"));
  }
  
  // Aktion
  if(szAction eq "FlatUp")
    if(GetPhase(pClonk)!=4) SetPhase(4,pClonk);
  if(GetAction(pClonk) ne szAction) return(-1);
}

func FxIntDecomposeStop(object pClonk, int iNumber, int iReason, bool fTemp) {
  if (fTemp) return();
  var pTarget = EffectVar(0,pClonk,iNumber);
  pTarget->SetBeingProcessed(false);
  return (1);
}

public func RejectEntrance(id idObj, object pObj) {
  if(IsBeingProcessed()) return(1);
  if(GetAction() eq "Decay") return(1);
  return(_inherited(idObj, pObj));
}