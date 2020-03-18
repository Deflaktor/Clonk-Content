#strict
#include PRNT

Initialize:
  return(1);

NoShiftOwner:
  return(!(GetAction()S="Idle"));

Hit:
  if(GetAction()S="TimeOver") BlowUp();
  Sound("RockHit*");
  if (Not(ActIdle())) return(1);
  Sound("Fuse");
  SetAction("Activated");
  return(1);

private BlowUp:
  CreateObject(KACX,0,0,GetOwner());
  if(!Local(0)) {
    var angle=Random(10);
    var power=5000+Random(1000);
    while(angle<360) {
      Var(0)=CreateObject(GetID(),-2+Random(4),-1+Random(5),GetOwner());
      SetLocal(0,1,Var(0));
      Var(0)->SetAction("TimeOver");
      Var(0)->SetSpeed(Sin(angle,power),Cos(angle,power));
      angle+=10;
    }
  }
  RemoveObject();
  return(1);

Activate:
  Hit();
  return(1);
  
