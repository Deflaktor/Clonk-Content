#strict

Start:  // INT RotationDir
  SetAction("Exist");
  SetR(Par(0));
  return(1);
Fade:
  SetClrModulation(RGBa(255,255,255,GetPhase()*24));
  return(1);
Remove:		return(RemoveObject());