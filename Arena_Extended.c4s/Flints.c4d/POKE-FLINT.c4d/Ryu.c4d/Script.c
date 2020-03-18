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

Attack:
  Sound("SHORYUKEN");
  SetXDir(0);
  SetYDir(-35);
  SetPosition(GetX(),GetY()-10);
  SetAction("Attack");
  Beat();
  return(1);

ReloadTime:
  return(5);

CloseDistance:
  return(10);

Jump:
  SetAction("Jump");
  SetYDir(-54);
  return(1);

Beat:
  while(SetVar(2,FindObject(0,-10,-20,20,40,OCF_Alive(),0,0,NoContainer(),Var(2))))
    if(GetOwner(Var(2))!=GetOwner()) {
      CastObjects(LEI8,5,10);
      DoEnergy(-40,Var(2));
      Fling(Var(2),-3+Random(6),-5-Random(1));
    }
  return(1);

ShotTarget:
  Sound("Hadouken");
  var x;
  x = -4 + 8 * GetDir();
  SetVar(0,CreateContents(_HDK));
  Exit(Var(0),0,3,0,x,0,0);
  SetOwner(GetOwner(),Var(0));
  return(1);

