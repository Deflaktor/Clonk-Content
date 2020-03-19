#strict

local wasOn, temporaryEnergy;

// Locals
// 0 Erstes Zielobjekt
// 1 Zweites Zielobjekt (invertiert)

Initialize:
  SetAction("NoEnergy");
  wasOn=false;
  return(1);
  
public SetTargets:
  SetLocal(0,Par(0));
  SetLocal(1,Par(1));
  return(1); 
  
Trigger:
  if(GetAction()S="NoEnergy")
    wasOn=!wasOn;
  else if(GetAction()S="On")
      SetAction("Off");
    else
      SetAction("On");
  return(1);
  
IsTriggerable:
  return(1);
  
public ControlUp:
  if(GetAction()S="Off")
    On(Par(0));
  return(1);
  
public ControlDownSingle:
  if(GetAction()S="On")
    Off(Par(0));
  return(1);
  
private On:
  if (!CheckEnergy()) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  Sound("Click");
  SetAction("On");
  
  if(!ObjectCall(Local(0), "Trigger", Par(0)))
    ObjectCall(Local(0),"ControlLeft");
  if(!ObjectCall(Local(1), "Trigger", Par(0)))
    ObjectCall(Local(1),"ControlRight");
  if(!ObjectCall(Local(2), "Trigger", Par(0)))
    ObjectCall(Local(2),"ControlLeft");
  if(!ObjectCall(Local(3), "Trigger", Par(0)))
    ObjectCall(Local(3),"ControlRight");
  if(Local(0)&&!Local(1))
    SetPlrView(GetOwner(Par(0)),Local(0));

  return(1);
private Off:
  if (!CheckEnergy()) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  Sound("Click");
  SetAction("Off");
  
  if(!ObjectCall(Local(0), "Trigger", Par(0)))
    ObjectCall(Local(0),"ControlRight");
  if(!ObjectCall(Local(1), "Trigger", Par(0)))
    ObjectCall(Local(1),"ControlLeft");
  if(!ObjectCall(Local(2), "Trigger", Par(0)))
    ObjectCall(Local(2),"ControlRight");
  if(!ObjectCall(Local(3), "Trigger", Par(0)))
    ObjectCall(Local(3),"ControlLeft");
  if(Local(0)&&!Local(1))
    SetPlrView(GetOwner(Par(0)),Local(0));

  return(1);

CheckEnergy:
  if (GameCall("MainEnergySupply", this())||temporaryEnergy>0) return(1);
  return(0);

AddEnergy:
  temporaryEnergy++;
  return(1);

Check:
  if(temporaryEnergy>0)
    temporaryEnergy--;
  if(!(CheckEnergy())) {
    if(GetAction()S="On") {
      wasOn = true;
      SetAction("NoEnergy");
      return(1);
    } 
    if(GetAction()S="Off") {
      wasOn = false;
      SetAction("NoEnergy");
      return(1);
    } 
  }
  if(CheckEnergy()) {
    if(GetAction()S="NoEnergy")
      if(wasOn)
        SetAction("On");
      else
        SetAction("Off");
  }
  return(1);
