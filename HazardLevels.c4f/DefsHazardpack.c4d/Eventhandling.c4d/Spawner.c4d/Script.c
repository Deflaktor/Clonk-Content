#strict
#include T_1_
/* Spawner */

local spawnID, spawnCall, spawnPar0, spawnPar1, spawnAmount, spawnCast, groupDelay, groupSize, amountLeft, amountAlive, lastSpawnedObject, container, bm2;

private func Initialize() {
  spawnAmount = 1;
  return(_inherited());
}

public func Copy() {
  var obj = inherited();
  obj->SetSpawnCast(spawnCast);
  obj->SetSpawnID(spawnID, spawnAmount);
  obj->SetSize(GetCon()/100);
  obj->SetFunctionCallToSpawned(spawnCall, spawnPar0, spawnPar1);
  obj->SetGroup(groupSize, groupDelay);
  obj->SetContainer(container);
  return(obj);
}

protected func AlternativeComment() {
  return(spawnCall);
}

public func Trigger(object pActuator) {
  if(spawnAmount<=0)
    spawnAmount=1;
  amountLeft += spawnAmount;
  return(_inherited(pActuator));
}

public func GetLastSpawned() {
  return(lastSpawnedObject);
}

protected func Execute(object pActuator, bool pDoNotSpawnNewOne) {
  var obj, eventContainer;
  if(container)
    if(GetID(container)==GetID()) {
      eventContainer=container->Execute(pActuator, true);
    }
  if(pDoNotSpawnNewOne)
    if(lastSpawnedObject)
      return(lastSpawnedObject);
	else
	  amountLeft++;
  var amount = amountLeft;
  if(groupSize)
    amount = Min(amount, groupSize);
  var x,y;
  for(var i=1;i<=amount;i++) {
    x=-5*(GetCon()-100)/100+Random(10*(GetCon()-100)/100);
    y=-5*(GetCon()-100)/100+Random(10*(GetCon()-100)/100);
    if(eventContainer)
      obj = CreateContents(spawnID, eventContainer);
    else {
      if(container)
	    obj = CreateContents(spawnID, container);
      else
        obj = CreateObject(spawnID, x, y);
    }
	if(spawnCast) {
      var ang=Random(360);
	  var lev = spawnCast;
      SetR(Random(360),obj);
	  var xdir;
      SetXDir(xdir=Cos(ang,lev)+RandomX(-3,3),obj);
      SetYDir(Sin(ang,lev)+RandomX(-3,3),obj);
      SetRDir((10+Random(21))*xdir/Abs(xdir),obj);
	}
    if(spawnCall) {
      ObjectCall(obj, spawnCall, spawnPar0, spawnPar1);
    }
	if(GetTarget())
	  AddEffect ("DeathCallback", obj, 10, 0, this());
	SetOwner(-1,obj);
	lastSpawnedObject = obj;
  }
  amountLeft -= amount;
  amountAlive += amount;
  if(amountLeft>0) {
    if(groupDelay==0) {
      if(GetAction()S="Showing")
        CreateObject(T01_)->Trigger();
      Execute(actuator);
      return(1);
    }
    timeToTrigger = groupDelay;
    if(GetAction()S="Showing")
      CreateObject(T01_)->Trigger(groupDelay);
  }
  return(obj);
}

public func SetSpawnCast(int power) {
  spawnCast = power;
}

public func SetGroup(int size, int delay) {
  groupSize = size;
  groupDelay = delay;
}

public func SetSpawnID(id pSpawnID, int amount) {
  spawnID = pSpawnID;
  spawnAmount = amount;
  return(spawnID);
}

public func SetSize(int sizeMultiplier) {
  if(sizeMultiplier<=0)
    sizeMultiplier=1;
  SetCon(sizeMultiplier*100);
  return(1);
}

public func SetFunctionCallToSpawned(string function, int par0, int par1) {
  spawnCall = function;
  spawnPar0 = par0;
  spawnPar1 = par1;
}

IsTriggerable:
  return(1);

public func DeathCallback(object pCaller) {
  amountAlive--;
  if(amountAlive<=0&&amountLeft<=0)
    if(GetTarget())
	  GetTarget()->Trigger();
}
  
protected func FxDeathCallbackStop(pTarget, iEffectNumber, iReason) {
  if (iReason == 4||iReason == 3) DeathCallback(pTarget);
  return(1);
}
  

public func SetContainer(object SetContainer, bool direct) {
  Var(1) = SetContainer;
  if(!Var(1)&&!direct) {
    Var(1) = FindContainer();
    if(!Var(1))
      return(Message("No nearby compatible container found."));
  }
  if(!ContainerCompatible(Var(1))&&!direct)
    return(Message("Container is not compatible."));
  Sound("SpawnPointSet");
  if(container) {
    SetObjectBlitMode(bm2, container);
  }
  container = Var(1);
  bm2 = GetObjectBlitMode(container);
  return(1);
}

private func ContainerCompatible(object pContainer) {
  if(GetID(pContainer)==GetID()||!(pContainer->~IsEventHandler()))
    return(1);
  return(0);
}

private func FindContainer(int distance, object skipTarget, id def) {
  Var(0) = skipTarget;
  if(distance == 0)
    distance = 30;
  while(Var(0) = FindObject(def,0,0,-1,-1,0,0,0,0,Var(0)))
    if(ContainerCompatible(Var(0)))
      if(Distance( GetX(),GetY(),GetX(Var(0)),GetY(Var(0)) ) < distance)
        return(Var(0));
  return(0);
}

protected func Destruction() {
  if(container) {
    SetObjectBlitMode(bm2, container);
  }
  return(_inherited());
}

protected func Timer() {
  if(_inherited()) {
    if(container&&!Contained()) {
      // Only show target when more than 20 pixels away to avoid blinking of the Command
      if(Distance(GetX(),GetY(),GetX(container),GetY(container))>20)
        SetCommand(this(), "MoveTo", 0, GetX(container), GetY(container), 0, true);
      if(EditCursor()==this()) {
        SetObjectBlitMode(3, container);
      } else {
        SetObjectBlitMode(bm, container);
      }
    } else {
      SetCommand(this(), "None");
    }
    return(1);
  }
  return(0);
}
