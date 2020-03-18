/*-- Robokoopa --*/

#strict
#include PIKA

local hits;

ShotLeft:
  SetDir(DIR_Left());
  SetVar(0,CreateObject(BLTZ));
  ObjectCall(Var(0),"Activate",GetX(),GetY(),-10,0,-1,3);
  SetOwner(GetOwner(),Var(0));
  SetComDir(COMD_Stop());
  return(1);

ShotRight:
  SetDir(DIR_Right());
  SetVar(0,CreateObject(BLTZ));
  ObjectCall(Var(0),"Activate",GetX(),GetY(),10,0,-1,3);
  SetOwner(GetOwner(),Var(0));
  SetComDir(COMD_Stop());
  return(1);
  
FarDistance:
  return(80);
  
CloseDistance:
  return(30);

ReloadTime:
  return(3);

CanShoot:
  if(GetAction() S= "Walk")
    return(1);
  return(0);
  
ShotLeft:
  SetDir(DIR_Left());
  Sound("smb3_jump");
  Jump();
  SetXDir(GetXDir()-10);
  SetPosition(GetX(),GetY()-10);
  return(1);

ShotRight:
  SetDir(DIR_Right());
  Sound("smb3_jump");
  Jump();
  SetXDir(GetXDir()+10);
  SetPosition(GetX(),GetY()-10);
  return(1);
  
Attack:
  if(!CanShoot())
    return(1);
  Sound("smb3_jump");
  SetPosition(GetX(),GetY()-10);
  Jump();
  SetAction("Attack");
  return(1);
  
Activity:
  if(GetAction()S="Jump") {
    Beat();
	if(GetX(this())>GetX(ziel)) SetXDir(BoundBy(GetXDir()-5,-30,30));
    else SetXDir(BoundBy(GetXDir()+5,-30,30));
  }
  if(GetAction()S="Attack") {
    Beat();
  	if(GetX(this())>GetX(ziel)+10) SetXDir(-25);
    else if(GetX(this())<GetX(ziel)-10) SetXDir(25);
	else SetXDir(0);
  }
  DoEnergy(4);
  return(inherited());
  
Beat:
  var hit=0;
  while(SetVar(2,FindObject(0,-10,-5,20,30,OCF_Alive(),0,0,NoContainer(),Var(2))))
    if(GetOwner(Var(2))!=GetOwner()&&GetYDir()>GetYDir(ziel)) {
      CastObjects(LEI8,5,10);
      DoEnergy(-40,Var(2));
	  hit=1;
    }
  if(hit) {
    hits++;
    Fling(Var(2),-3+Random(6),5-Random(1));
    SetPosition(GetX(),GetY()-10);
    SetYDir(-20);
    SetAction("Attack");
	if(hits>7) {
	  Sound("1up");
	  CastObjectsX(ST58,hits-7,60,0,0,270,45,"Sett");
	} else
	  Sound(Format("combohit%d",hits));
  }
  return(1);
  
Sett:
  SetOwner(-1, Par(0));
  return(1);