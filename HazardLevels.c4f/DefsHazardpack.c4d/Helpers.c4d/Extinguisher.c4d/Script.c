/*-- Brennende Objekte nach einiger Zeit löschen --*/

#strict

Check:
  if(GetAction()ne"Idle") return(0);
  while(Var()=FindObject(0,0,0,0,0,OCF_OnFire(),0,0,0,Var()))
    if(!FindObject(GetID(),0,0,0,0,0,0,Var()))
      ObjectSetAction(CreateObject(GetID(),0,0,-1),"IsOnFire",Var());
  return(1);

DoExtinguish:
  if(!GetAlive(GetActionTarget())) return(RemoveObject());
  if(GetActTime()>150) {
    Extinguish(GetActionTarget());
    return(RemoveObject());
  }
  return(1);

WasExtinguished:
  if(!GetAlive(GetActionTarget())) return(RemoveObject());
  if(!OnFire(GetActionTarget())) return(RemoveObject());
  return(1);

Activate:
  MessageWindow(GetDesc(),Par());
  return(1);