/*-- Kraftfeld --*/
#strict
local oldX, oldY, counter, target;


/* Wird erstellt. Par(1) ist Zielobjekt. */
public func Launch(int dir, object generator) {
  SetAction("Exist",generator);
  target = Contained(generator);
  MakeInvisible(this());
  MakeInvisible(target);
  oldX = GetX();
  oldY = GetY();
  return(1);
}

private func MakeInvisible(object obj) {
  AddEffect("Invis", obj, 260, 20, 0, GetID(), this());
}

private func MakeVisible(object obj) {
  // Von Effektzahl abwärts zählen, da Effekte entfernt werden
  var i = GetEffectCount(0, obj), iEffect;
  while (i--)
    if (iEffect = GetEffect("Invis", obj, i))
      EffectCall(obj, iEffect, "Timer");
}

private func MakeAllVisible() {
  var obj;
  // Alle Objekte durchsuchen
  while (obj=FindObject(0, -60,-60,120,120, 0, 0,0, 0, obj)) {
    MakeVisible(obj);
  }
}
  
ReduceCounter:
  counter+=Par(0);
  return(1);

/* Kraftfeld-Aktion */
public CheckField:
  if(!GetActionTarget()) {
    return(RemoveObject());
  }
  SetPosition(GetX(GetActionTarget()),GetY(GetActionTarget()));
  // Sich bewegen kostet doppelt
  if(oldX!=GetX()||oldY!=GetY())
    counter++;
  // Wenn in einem Gebäude drin, kostet es nichts
  if(!(GetCategory(Contained(GetActionTarget())) & (C4D_StaticBack() | C4D_Structure()) || Contained(Contained(GetActionTarget()))))
    counter++;
  oldX = GetX();
  oldY = GetY();
  MunUpdate();
  if(!Contained(GetActionTarget())) {
    target = 0;
    SetOwner(-1);
    var clonkNearby = false;
    // mach alles drum rum unsichtbar außer generator
    while(SetVar(0,FindObject(0,-50,-50,100,100,0,0,0,NoContainer(),Var(0)))) 
      if(Var(0)!=GetActionTarget())
        if(ObjectDistance(Var(0))<23) {
          MakeInvisible(Var(0));
          if(GetOCF(Var(0)) & OCF_CrewMember())
            clonkNearby = true;
        }
    // Im freien zu sein kostet weniger
    if(clonkNearby && !Random(3))
      counter++;
  } else if(target!=Contained(GetActionTarget())) {
    // target wechsel?
    MakeVisible(target);
    // target wechsel kostet
    counter++;
  }
  target = Contained(GetActionTarget());
  SetOwner(GetOwner(target));
  MakeInvisible(target);
  var maxcounter;
  maxcounter = 900;
  if(counter>=maxcounter*4/4) return(Disable());
  if(counter>=maxcounter*3/4) return(SetDir(3));
  if(counter>=maxcounter*2/4) return(SetDir(2));
  if(counter>=maxcounter*1/4) return(SetDir(1));
  return(1);

MunUpdate:
  var maxcounter;
  maxcounter = 900;
  ObjectCall(GetActionTarget(),"EnergyUpdate",Contained(GetActionTarget()),100-(100*counter/maxcounter));
  return(1);

public Disactivate:
  SetAction("Idle");
  MakeAllVisible();
  return(1);

public Disable:
  ObjectSetAction(GetActionTarget(),"Idle");
  RemoveObject();
  MakeAllVisible();
  return(1);

// EffectVars:
//   0 - Vorheriger Sichtbarkeitsstatus
//   1 - Vorherige Farbmodulation
//   2 - das Invisible forceField object (dieses script als object)
protected func FxInvisStart(object pTarget, int iEffectNumber, int iTemp, object forceField) {
  // Vorherige Sichtbarkeit des Zauberers speichern
  EffectVar(0, pTarget, iEffectNumber) = VIS_All();//GetVisibility(pTarget);
  EffectVar(1, pTarget, iEffectNumber) = RGBa(255,255,255,0);//GetClrModulation(pTarget);
  EffectVar(2, pTarget, iEffectNumber) = forceField;
  // Zauberer unsichtbar machen
  SetVisibility(VIS_Owner() | VIS_God(), pTarget);
  // Halbdurchsichtig bläulich für den Besitzer und Verbündete
  // SetClrModulation(ModulateColor(GetClrModulation(pTarget),RGBa(127,127,255,127)), pTarget);
  SetClrModulation(RGBa(127,127,255,127), pTarget);
  // Fertig
  return(1);
}

protected func FxInvisStop(object pTarget, int iEffectNumber, int iCause, bool fTemp) {
  // Status wiederherstellen
  SetVisibility(   EffectVar(0, pTarget, iEffectNumber), pTarget);
  SetClrModulation(EffectVar(1, pTarget, iEffectNumber), pTarget);
  // Fertig
  return(1);
}

protected func InvisibilityCheck(object forceField, object pTarget) {
  // ForceField gelöscht?
  if(!forceField) return(0);
  // ForceField deaktiviert?
  if(ActIdle(forceField)) return(0);
  // Generator in einem Container und target ist nicht der Container?
  if(Contained(forceField->GetActionTarget()))
    if(Contained(forceField->GetActionTarget())!=pTarget) 
      if(forceField!=pTarget) return(0);
  // Zu weit weg?
  if(forceField->ObjectDistance(pTarget)>23) return(0);
  return(1);
}

protected func FxInvisTimer(object pTarget, int iEffectNumber, int iEffectTime) {
  var forceField = EffectVar(2, pTarget, iEffectNumber);

  if(!InvisibilityCheck(forceField, pTarget)) {
    // wenn noch weitere instancen von diesem effekt da sind, dann lösche den effekt ohne wieder sichtbar zu machen
    if(GetEffectCount("Invis", pTarget) > 1) {
      RemoveEffect(0, pTarget, iEffectNumber, 1);
      return(1);
    } else {
      // es gibt keine anderen instanzen -> normales stop und object wieder sichtbar machen
      return(-1);
    }
  }

  return(1);
}

protected func FxInvisEffect(szNewEffect, pTarget, iEffectNumber, int iNewEffectNumber, object forceField) {
  // Andere Unsichtbarkeitszauber aufnehmen
  if (SEqual(szNewEffect, "Invis")) {
    //if(EffectVar(2, pTarget, iEffectNumber) == forceField)
      return(-1);
    //else {
      /*EffectVar(0, pTarget, iNewEffectNumber) = EffectVar(0, pTarget, iEffectNumber);
      EffectVar(1, pTarget, iNewEffectNumber) = EffectVar(1, pTarget, iEffectNumber);*/
    //}
  }
  // Sonst keine Behandlung
  return();
}

/*
protected func FxInvisAdd(object pTarget, int iEffectNumber, string szNewEffect, int iNewTimer) {
  // Effekt aufrechnen: Rest vom alten Timer ermitteln
  GetEffect(0, pTarget, iEffectNumber, 3) - GetEffect(0, pTarget, iEffectNumber, 6);
  // Diesen Effekt mit neuem Timer weiterführen
  ChangeEffect(0, pTarget, iEffectNumber, szNewEffect, iOldTimer + iNewTimer);
  // Fertig
  return(0);
}*/