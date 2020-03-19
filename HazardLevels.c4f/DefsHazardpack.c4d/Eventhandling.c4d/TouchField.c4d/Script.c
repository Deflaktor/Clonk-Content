#strict
#include T_1_
/* TouchField */

local triggerOnce, clonksOnly, itemsToo;

protected func Initialize() {
  triggerOnce=true;
  clonksOnly=true;
  SetSize(5);
  return(_inherited());
}

public func Copy() {
  var obj = inherited();
  obj->SetTriggerOnce(triggerOnce);
  obj->SetClonksOnly(clonksOnly);
  obj->SetItemsToo(itemsToo);
  obj->SetSize(GetCon()/100);
  return(obj);
}


public func SetTriggerOnce(bool pTriggerOnlyOnce) {
  triggerOnce=pTriggerOnlyOnce;
  return(triggerOnce);
}

public func SetClonksOnly(bool pClonksOnly) {
  clonksOnly = pClonksOnly;
  return(clonksOnly);
}

public func SetItemsToo(bool pItemsToo) {
  itemsToo = pItemsToo;
  return(itemsToo);
}

protected func Timer() {
  _inherited();
  if(!IsActive()||Contained())
    return(1);
  var ocf;
  if(clonksOnly)
    ocf = OCF_CrewMember();
  else
    ocf = OCF_Prey();
  while(SetVar(0,FindObject(0,-5*GetCon()/100,-5*GetCon()/100,10*GetCon()/100,10*GetCon()/100,ocf,0,0,NoContainer(),Var(0)))) {
    Trigger(Var(0));
    if(triggerOnce)
      return(SetActive(0));
  }
  Var(0)=0;
  if(itemsToo)
    while(SetVar(0,FindObject(0,-5*GetCon()/100,-5*GetCon()/100,10*GetCon()/100,10*GetCon()/100,OCF_Collectible,0,0,NoContainer(),Var(0)))) {
      Trigger(Var(0));
      if(triggerOnce)
        return(SetActive(0));
    }
  
  return(1);
}

public func SetSize(int sizeMultiplier) {
  if(sizeMultiplier<=0)
    sizeMultiplier=1;
  SetCon(sizeMultiplier*100);
  return(1);
}