#strict
#include _PEM

Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  SetOwner(-1);
  SetMyColor();
  return(1);

SetMyColor:
  if(GetOwner()==-1)
    SetColorDw(RGBa(255, 255, 255, 0));
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

Zerfetzen:
  Bluten(100);
  CastObjects(MEAT, 1, 20);
  return(1);

Death:
  var threattype = Random(11);
  if(threattype == 10)
  CreateObject(S582,0,0,GetOwner(this()));
  if(threattype < 10)
  CreateObject(ST58,0,0,GetOwner(this()));
  Sound("Die");
  Zerfetzen();
// Hatte leider keine Zeit mehr, Kristalle einzubauen
//  if(Not(Random(150))) CastObjects(_RUB,1,30);
//  if(Not(Random(150))) CastObjects(_RUG,1,30);
//  if(Not(Random(150))) CastObjects(_RUR,1,30);
  RemoveObject(this());
  return(1);
DeepBreath:
  Sound("Breath");
  return(1);
Redefine:
  ChangeDef(Par(0));
  SetAction("Walk");
  return(1);

Activity:
  if(SEqual(GetAction(this()),"Dead")) return(1);
  while(Var(0)=FindObject(0,0,0,-1,-1,OCF_Prey(),0,0,0,Var(0)))
    if(GetOwner(Var(0))!=GetOwner()) {
      Local(0)=Var(0);
      break;
    }
  if(Local(0)) {
    SetCommand(this(),"MoveTo",Local(0));
    HasEnemy();
  }

  if(Equal(GetDir(this()),DIR_Left()))  if(GBackSolid(-10,0)) if(Not(SEqual(GetAction(this()),"Tumble"))) And(SetAction("Jump"),SetYDir(-75));
  if(Equal(GetDir(this()),DIR_Right())) if(GBackSolid(10,0))  if(Not(SEqual(GetAction(this()),"Tumble"))) And(SetAction("Jump"),SetYDir(-75));
  if(Equal(GetDir(this()),DIR_Left()))  if(GBackSolid(-5,0))  DigFree(GetX(this()),GetY(this()),13);
  if(Equal(GetDir(this()),DIR_Right())) if(GBackSolid(5,0))   DigFree(GetX(this()),GetY(this()),13);
  if(Not(Equal(GetDir(this()),DIR_Left())))   if(GBackSolid(-10,8)) if(Not(SEqual(GetAction(this()),"Jump"))) And(SetAction("Jump"),SetYDir(-54));
  if(Not(Equal(GetDir(this()),DIR_Right())))  if(GBackSolid(10,8))  if(Not(SEqual(GetAction(this()),"Jump"))) And(SetAction("Jump"),SetYDir(-54));
  if(Not(Equal(GetDir(this()),DIR_Left())))   if(GBackSolid(-50,8)) And(SetDir(DIR_Left()),SetComDir(COMD_Left()));
  if(Not(Equal(GetDir(this()),DIR_Right())))  if(GBackSolid(50,8))  And(SetDir(DIR_Right()),SetComDir(COMD_Right()));
  return(1);

HasEnemy:
  if(Distance(GetX(),GetY(),GetX(Local(0)),GetY(Local(0)))<40) {
    Shot();
    if(Not(Random(12))) 
      SetDir(Random(2));
  }
  return(1);

Shot:
  if(GreaterThan(GetX(this()),GetX(Local(0)))) if(Not(SEqual(GetAction(this()),"Tumble"))) ShotLeft();
  if(LessThan(GetX(this()),GetX(Local(0))))    if(Not(SEqual(GetAction(this()),"Tumble"))) ShotRight();
  return(1);

ShotLeft:
  SetDir(DIR_Left());
  Var(0)=CreateContents(_WSP);
  SetOwner(GetOwner(),Var(0));
  Exit(Var(0),-8,-1,0,-8,0,0);
  SetComDir(COMD_Stop());
  return(1);

ShotRight:
  SetDir(DIR_Right());
  Var(0)=CreateContents(_WSP);
  SetOwner(GetOwner(),Var(0));
  Exit(Var(0),+8,-2,0,+8,0,0);
  SetComDir(COMD_Stop());
  return(1);
