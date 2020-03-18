#strict
#include PRNT

NoShiftOwner:
  return(!(GetAction()S="Idle"));

SoundHalleluja:
  Sound("Halleluja",1);
  return(1);

Grow:
  Local(0)++;
  DoCon((Local(0)+1)*(Local(0)+1)*10);
  if(Local(0)>3) {
    Local(0)=0;
    BlowUp();
  }
  return(1);
  
private BlowUp:
  CreateObject(KACX,0,0,GetOwner());
  RemoveObject();
  return(1);

Effect:
  CastObjects(SPRK, 1, 20);
  Local(0)++;
  if(Local(0)>=10) {
    Local(0)=0;
    SetAction("Halleluja");
  }
  return(1);
  
Hit:
  if(GetAction() S= "Idle") 
    SetAction("Activated");
  Sound("RockHit*");
  return(1);