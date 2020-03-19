#strict

local grabber;

// Locals
// 0: Zielobjekt

protected Initialize:
  SetAction("On");
  return(1);
  
public SetTarget:
  SetLocal(0,Par(0));
  return(1); 
  
public ControlUp:
  if(!SchalterGedruckt(Par(0))) return(1);
  ObjectCall(Local(0),"ContainedUp");
  return(1);
  
public ControlDownSingle:
  if(!SchalterGedruckt(Par(0))) return(1);
  ObjectCall(Local(0),"ContainedDown");
  return(1);
  
public ControlLeft:
  if(!SchalterGedruckt(Par(0))) return(1);
  if(GetDir(Local(0))==DIR_Left()) {
	if(GetXDir(Local(0))>-15) SetXDir(-15, Local(0));
	if(Local(0)->GetAction() S= "Hover")
      return(1);
  }
  ObjectCall(Local(0),"ContainedLeft");
  return(1);  
  
public ControlRight:
  if(!SchalterGedruckt(Par(0))) return(1);
  if(GetDir(Local(0))==DIR_Right()) {
    if(GetXDir(Local(0))>15) SetXDir(15, Local(0));
	if(Local(0)->GetAction() S= "Hover")
      return(1);
  }
  ObjectCall(Local(0),"ContainedRight");
  return(1);  
  
SchalterGedruckt:
  if(GetAction()S="On") {
    grabber = Par(0);
    return(1);
  }
  Sound("Error");
  Message("Nicht genug Energie.",this());
  return(0);
  
Check:
  if(!(CheckEnergy())) {
    if(GetAction()S="On") {
      SetAction("NoEnergy");
      return(1);
    } 
  }
  if(CheckEnergy()) {
    if(GetAction()S="NoEnergy")
      SetAction("On");
	if(grabber) {
	  if(!(grabber->GetAction() S= "Push")) {
	    grabber=0;
		SetComDir(COMD_Stop(), Local(0));
		SetXDir(0, Local(0));
	  }
	}
  }
  return(1);
  
CheckEnergy:
  if (GameCall("MainEnergySupply", this())) return(1);
  return(0);
  
 