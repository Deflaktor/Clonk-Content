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
  
public ControlLeft:
  [�ffnen]
  return(On(Par(0)));  
public ControlRight:
  [Schlie�en]
  return(Off(Par(0)));

private On:
  if (!CheckEnergy()) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  Sound("Click");
  SetAction("On");
  
  SwitchLeft(Local(0), Par(0));
  SwitchRight(Local(1), Par(0));
  SwitchLeft(Local(2), Par(0));
  SwitchRight(Local(3), Par(0));
  
  if(Local(0)&&!Local(1))
    SetPlrView(GetOwner(Par(0)),Local(0));

  return(1);
  
private Off:
  if (!CheckEnergy()) return(And( Sound("Error"), Message("Nicht genug Energie.",this()) ));
  Sound("Click");
  SetAction("Off");
  
  SwitchRight(Local(0), Par(0));
  SwitchLeft(Local(1), Par(0));
  SwitchRight(Local(2), Par(0));
  SwitchLeft(Local(3), Par(0));
  
  if(Local(0)&&!Local(1))
    SetPlrView(GetOwner(Par(0)),Local(0));

  return(1);


SwitchLeft:
  if(!Par(0)) return(0);
  if(Par(0)->~IsTriggerable()) return(Par(0)->Trigger(Par(1))); else return(Par(0)->~ControlLeft());
  return(0);
  
SwitchRight:
  if(!Par(0)) return(0);
  if(Par(0)->~IsTriggerable()) return(Par(0)->Trigger(Par(1))); else return(Par(0)->~ControlRight());
  return(0);
  
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
