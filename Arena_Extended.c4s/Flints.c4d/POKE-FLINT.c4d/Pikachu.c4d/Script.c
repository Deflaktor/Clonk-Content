#strict

local ziel,reloaden;

Completion:
  SetAction("Walk");
  SetDir(Random(2));
  SetEntrance(1);
  return(1);

Grab:
  Sound("Grab");
  return(1);

Get:
  Sound("Grab");
  return(1);

Put:
  Sound("Grab");
  return(1);

Death:
  CastObjects(SPRK,20,20);
  CastObjects(SPRK,20,40);
  CastObjects(SPRK,20,10);
  RemoveObject(this());
  return(1);

DeepBreath:
  Sound("Breath");
  return(1);

Redefine:
  ChangeDef(Par(0));
  SetAction("Walk");
  return(1);

Damaged:
  DoEnergy(-Par(0));
  return(1);
  
Activity:
  if(SEqual(GetAction(this()),"Dead")) return(1);
  var neuesZiel;
  while(neuesZiel = FindObject(0,0,0,-1,-1,OCF_Alive(),0,0,NoContainer(),neuesZiel))
    if(GetOwner() != GetOwner(neuesZiel)) {
      ziel=neuesZiel;
      SetCommand(this(),"MoveTo",0,GetX(ziel)+CloseDistance()-Dir2Target(ziel)*CloseDistance(),GetY(ziel));
      HasEnemy();
      break;
    }
  if(!ziel)
    SetComDir(COMD_Stop());
  if(Not(Equal(GetDir(this()),DIR_Left())))   if(GBackSolid(-10,8)) if(Not(SEqual(GetAction(this()),"Jump"))) Jump();
  if(Not(Equal(GetDir(this()),DIR_Right())))  if(GBackSolid(10,8))  if(Not(SEqual(GetAction(this()),"Jump"))) Jump();
  if(Not(Equal(GetDir(this()),DIR_Left())))   if(GBackSolid(-50,8)) And(SetDir(DIR_Left()),SetComDir(COMD_Left()));
  if(Not(Equal(GetDir(this()),DIR_Right())))  if(GBackSolid(50,8))  And(SetDir(DIR_Right()),SetComDir(COMD_Right()));
  if(Equal(GetDir(this()),DIR_Left()))  if(GBackSolid(-3,0))  DigFree(GetX(this()),GetY(this()),13);
  if(Equal(GetDir(this()),DIR_Right())) if(GBackSolid(3,0))   DigFree(GetX(this()),GetY(this()),13);
  
  if(GetXDir()>1)
    SetDir(DIR_Right());
  if(GetXDir()<-1)
    SetDir(DIR_Left());

 /* if(!Random(5)||Distance(GetX(),GetY(),GetX(ziel),GetY(ziel))<CloseDistance())
    SetComDir(COMD_Stop());*/
  DoEnergy(-5);
  return(1);

Dir2Target:
  if(GetX()<GetX(Par(0))) return(1);
  return(0);

CloseDistance:
  return(50);

FarDistance:
  return(150);

Jump:
  SetAction("Jump");
  SetYDir(-54);
  return(1);

ReloadTime:
  return(3);

HasEnemy:
  reloaden--;
  if(Distance(GetX(),GetY(),GetX(ziel),GetY(ziel))<CloseDistance()) return(Attack());
  if(reloaden>0)
    return(0);
  reloaden=ReloadTime();
  if(Distance(GetX(),GetY(),GetX(ziel),GetY(ziel))<FarDistance()) return(Shot());
  return(1);

Attack:
  return(Shot());

Shot:
  if(GreaterThan(GetX(this()),GetX(ziel))) if(CanShoot()) ShotLeft();
  if(LessThan(GetX(this()),GetX(ziel)))    if(CanShoot()) ShotRight();
  return(1);

CanShoot:
  if(GetAction() S= "Tumble")
    return(0);
  return(1);

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
