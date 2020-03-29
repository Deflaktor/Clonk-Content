/*-- Ozark --*/

#strict
#include OZRK

private DoJump:
  SetComDir(COMD_None());
  return(1);

private Walking:
  SetComDir(COMD_None());
  SmackPrey();
  return(1);

private TurnRight:
  SetComDir(COMD_None());
  return(1);

private TurnLeft:
  SetComDir(COMD_None()); 
  return(1);
  
public Reproduction:
  return(1);
  
Range:
  return(350);
  