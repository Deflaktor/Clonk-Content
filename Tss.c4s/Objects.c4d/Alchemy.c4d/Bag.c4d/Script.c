#strict

protected func Activate(pCaller)
{
  [$CtrlActivateBag$]
  var pBag = pCaller;
  // Clonk hat schon eine Tasche?
  if(AlchemBag(pBag)) 
  {
    // Meldung dass er schon einen hat
    PlayerMessage(GetOwner(pCaller), "$MsgAlreadyHasBag$", pCaller, pCaller->GetName());
    return(1);  
  }   
  // an den Clonk heften
  BelongTo(pCaller);
  Sound("Connect",0,0,0,GetOwner(pCaller)+1);
  PlayerMessage(GetOwner(pCaller),"$MsgPuton$",pCaller);
  return(1);
}

public func Exhaustion()
{
  // angeheftet muss der Beutel dableiben
  if(GetAction()eq"Belongs") return(true);
  // im Inventar, etc
  return(true);
}

public func BelongTo(object pObject) { SetAction("Belongs",pObject); }

// Menü für Alchemie, das im Clonk auftaucht, an den der Beutel gehaengt ist
protected func AttachContextAlchem(object pActionTarget, object pObj, int iSelection)
{
  [$CtxAlchemy$|Image=ALC_]

  // Clonk soll anhalten
  pActionTarget->SetComDir(COMD_Stop());

  var i, j, idAlchem;
  // Kontextmenü erzeugen
  CreateMenu(ALC_,pActionTarget,0,0,"$CtxAlchemy$",0,1,0);

  // zerlegen/entleeren (nur wenn nicht Contained())
  if(!Contained(pActionTarget) && Ready2Decompose()) {
    var pAlchemContainer, idAlchem, szName;
    for(;pAlchemContainer=AlchemContainer(i,pActionTarget);++i) {
      if(pAlchemContainer->~AlchemProcessTime() == 0) { // was zum rausnehmen
        AddMenuItem(Format("$MnuExhaust$",GetName(pAlchemContainer)),"Decompose",GetID(pAlchemContainer),pActionTarget,0,pAlchemContainer);
      } else {
        AddMenuItem(Format("$MnuDecompose$",GetName(pAlchemContainer)),"Decompose",GetID(pAlchemContainer),pActionTarget,0,pAlchemContainer);
      }
    }
  }

  //AddMenuItem("$MnuExhaustAll$","StoreNearby",ALC_,pActionTarget);

  AddMenuItem("$MnuIndex$","Index",ALC_,pActionTarget);
  AddMenuItem("$MnuDeposit$","Loose",BMSD,pActionTarget);
  AddMenuItem("$MnuHelp$","HelpTxt",CXIN,pActionTarget);

  return(1);
}


StoreNearby:
  Var(0)=0;
  var container;
  container=Contained(GetActionTarget());
  while(Var(0)=FindObject(0,-30,-20,60,40,0,0,0,container,Var(0))) {
    if(ObjectCall(Var(0), "IsAlchemMaterial")) {
      Exit(Var(0));
      Enter(this(), Var(0));
    }
  }
  return(1);

private func Decompose(id idType, object pObject) {
  // sofort zerlegen
  if(pObject->~AlchemProcessTime() == 0) Transfer(pObject);
  else AddEffect("IntDecompose",GetActionTarget(),1,1,0,GetID(),pObject,this());
}

public func Loose() {
  PlayerMessage(GetOwner(GetActionTarget()),"$MsgDeposit$",GetActionTarget());
  var pEnter = Contained(GetActionTarget());
  SetAction("Idle");
  SetActionTargets();
  if(pEnter) Enter(pEnter);
}

public func HelpTxt() {
  MessageWindow("$MsgHelpTxt$",GetOwner(GetActionTarget()),CXIN,"$MnuHelp$");
}

public func Index() {
  // keine Zutaten vorhanden
  if(!Contents()) {
    MessageWindow("$MsgEmpty$",GetOwner(GetActionTarget()),ALC_,"$MnuIndex$");
  }
  // Zutaten vorhanden
  else {
    CreateMenu(ALC_,GetActionTarget(),0,0,"$MnuIndex$",0,1,0);
    var objAlchem, objOldAlchem;
    for(var i=0; objAlchem=Contents(i); ++i) {
      if(GetID(objOldAlchem)!=GetID(objAlchem))
        AddMenuItem(GetName(objAlchem),"GetOut",GetID(objAlchem),GetActionTarget(),ContentsCount(GetID(objAlchem)),objAlchem);
      objOldAlchem = objAlchem;
    }
  }
}

GetOut:
  // Exit(Par(1));
  return(Index());

func FxIntDecomposeStart(object pClonk, int iNumber, int iTemp, object pAlchemContainer, object pAlchemManager)
{
  var szAct;
  EffectVar(0,pClonk,iNumber) = pAlchemContainer;
  EffectVar(1,pClonk,iNumber) = pAlchemManager;
  // Process vorhanden? toll. Nicht vorhanden? nich so toll.
  // ...aber möglich!! :)
  if(GetActMapVal("Name","Process",GetID(pClonk)))
    szAct = "Process";
  else
    szAct = "FlatUp";
  pClonk->SetAction(szAct);
  EffectVar(2,pClonk,iNumber) = szAct;
  // Objekt vor sich hinlegen
  Exit(pAlchemContainer,GetX(pClonk)-10+GetDir(pClonk)*20,GetY(pClonk)+12);
}

func FxIntDecomposeTimer(object pClonk, int iNumber, int iEffectTime) {
  var pAlchemContainer = EffectVar(0,pClonk,iNumber),
      pAlchemManager = EffectVar(1,pClonk,iNumber),
      szAction = EffectVar(2,pClonk,iNumber);

  // Objekt weg
  if( !pAlchemContainer || Contained(pAlchemContainer)
   || Abs(GetX(pAlchemContainer)-GetX(pClonk)) > 15 || Abs(GetY(pAlchemContainer)-GetY(pClonk)) > 15 )

        return(-1,pClonk->SetAction("KneelUp"));

  // Beutel weg
  if(!pAlchemManager || !GetAlchemBag(pClonk)) return(-1,pClonk->SetAction("KneelUp"));

  // Zeit abgelaufen
  if(iEffectTime >= pAlchemContainer->~AlchemProcessTime())
    return(-1,pAlchemManager->Transfer(pAlchemContainer));

  // Aktion
  if(szAction eq "FlatUp")
    if(GetPhase(pClonk)!=4) SetPhase(4,pClonk);
  if(GetAction(pClonk) ne szAction) return(-1);


}

public func Transfer(object pObject) {

  // Clonk wieder hinstellen
  if(GetAction(GetActionTarget()) ne "Walk")
    GetActionTarget()->SetAction("KneelUp");

  PlayerMessage(GetOwner(GetActionTarget()),Format("$MsgReceived$.",TransferAlcStr(pObject)),this());
  // und nun den Inhalt rüberschieben
  Enter(this(),pObject);
  Split2Components (pObject);
 }

private func TransferAlcStr(object pObject, int iMul) {
  var idAlchem, iAlchem, szMessage;

  szMessage = "";
  
  for(var i=0; idAlchem = GetComponent(0, i, 0, GetID(pObject)); i++) {
    iAlchem = GetComponent(idAlchem,0,0,GetID(pObject));
    szMessage = Format("%s|%dx{{%i}}%s",szMessage,iAlchem,idAlchem,GetName(0,idAlchem));
  }


  return(szMessage);
}


protected func Ready2Decompose() { if(GetActionTarget()) if(GetAction(GetActionTarget()) eq "Walk") return(1);  }

protected func RejectEntrance() { if(GetAction()eq"Belongs") return(1); }

protected func Hit() { Sound("WoodHit*"); }

/* Produkteigenschaften */

public func IsAnvilProduct() { return(1); }

// public func IsLorry() { return(1); }