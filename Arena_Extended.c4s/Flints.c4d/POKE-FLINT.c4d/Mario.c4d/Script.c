#strict
#include PIKA

ShotLeft:
  SetDir(DIR_Left());
  SetAction("Throw");
  SetComDir(COMD_Stop());
  return(1);

ShotRight:
  SetDir(DIR_Right());
  SetAction("Throw");
  SetComDir(COMD_Stop());
  return(1);

CanShoot:
  if(!(GetAction() S= "Walk"))
    return(0);
  return(1);

ReloadTime:
  return(1);

CloseDistance:
  return(40);

Jump:
  SetAction("Jump");
  SetYDir(-54);
  Sound("smb3_jump");
  return(1);

ShotTarget:
  Sound("smb3_fireball");
  var x;
  x = -4 + 8 * GetDir();
  SetVar(0,CreateContents(_MFB));
  Exit(Var(0),0,-2,0,x,0,40);
  SetOwner(GetOwner(),Var(0));
  return(1);

