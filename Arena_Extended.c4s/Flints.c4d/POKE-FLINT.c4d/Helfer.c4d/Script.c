#strict
#include PIKA

ShotLeft:
  SetDir(DIR_Left());
  ShotTarget();
  SetComDir(COMD_Stop());
  return(1);

ShotRight:
  SetDir(DIR_Right());
  ShotTarget();
  SetComDir(COMD_Stop());
  return(1);

ReloadTime:
  return(1);

ShotTarget:
  var x,y,angle,speed;
  speed = 10;
  angle = Angle(GetX(),GetY(),GetX(ziel),GetY(ziel)+8);
  x = Sin(angle,speed);
  y = Cos(angle,speed);
  SetVar(0,CreateContents(_WST));
  Exit(Var(0),0,-2,0,x,-y,40);
  SetOwner(GetOwner(),Var(0));
  return(1);