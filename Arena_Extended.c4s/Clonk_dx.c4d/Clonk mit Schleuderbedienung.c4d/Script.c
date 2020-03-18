/*-- Clonk DX --*/
#strict
#include CLON

Schleuder:
  Message("Die hast du doch schon",this());
  Sound("Error");
  return(1);

Kaze:
  Message("Du hast bereits Schleuder!",this());
  Sound("Error");
  return(1);

ControlSpecial2:
  if(SEqual(GetAction(this()),"Walk"))   SetAction("Zielen");
  if(SEqual(GetAction(this()),"Jump"))   ShotIt();
  if(SEqual(GetAction(this()),"Zielen")) SetPhase(4);
  return(1);

ControlSpecial2Double:
  if(SEqual(GetAction(this()),"Zielen")) SetAction("Walk");
  return(1);

ControlDown:
  if(SEqual(GetAction(this()),"Zielen")) if(LessThan(GetPhase(this()),6)) SetPhase(Sum(GetPhase(this()),+1),this());
  SetComDir(COMD_Stop());
  return(0);

ControlUp:
  if(SEqual(GetAction(this()),"Zielen")) if(GreaterThan(GetPhase(this()),0)) SetPhase(Sum(GetPhase(this()),-1),this());
  if(Equal(GetDir(),DIR_Left())) if(Not(SEqual(GetAction(this()),"Tumble"))) if(GreaterThan(GetMagicEnergy(),1)) if(SEqual(GetAction(this()),"Jump")) MagicJumpLeft();
  if(Equal(GetDir(),DIR_Right())) if(Not(SEqual(GetAction(this()),"Tumble"))) if(GreaterThan(GetMagicEnergy(),1)) if(SEqual(GetAction(this()),"Jump")) MagicJumpRight();
  SetComDir(COMD_Stop());
  return(0);

protected ControlThrow:
  if(Contents())   if ( !GetPlrDownDouble(GetOwner()) ) if(SEqual(GetAction(this()),"Walk")) ObjectCall(Contents(0),"Check", this());
  if(Contents()) if(SEqual(GetAction(this()),"Zielen")) ObjectCall(Contents(0),"Check", this());
  if(Contents()) if(SEqual(GetAction(this()),"Zielen")) ZielWurf();
  return(0);


ShotIt:
  if(Equal(GetDir(),DIR_Left())) if(Not(SEqual(GetAction(this()),"Tumble"))) ShotLeft();
  if(Equal(GetDir(),DIR_Right())) if(Not(SEqual(GetAction(this()),"Tumble"))) ShotRight();
  return(1);

ShotLeft:
  Sound("Punch2");
  if(Equal(Local(0),1)) ObjectCall(FindOtherContents(CD58),"Check", this());
  Var(0)=Contents();
  Exit(Var(0),-12,0,0,-24,0,0);
  ObjectCall(Var(0), "Shot");
  return(1);

ShotRight:
  Sound("Punch2");
  if(Equal(Local(0),1)) ObjectCall(FindOtherContents(CD58),"Check", this());
  Var(0)=Contents();
  Exit(Var(0),+12,0,0,+24,0,0);
  ObjectCall(Var(0), "Shot");
  return(1);


//(aus dem Hazard Pack)
ZielWurf: 
  Sound("Punch2");
  SetVar(8,GetDir(this()));
  SetVar(9,GetPhase(this()));
  SetVar(4,Mul(Var(9),4));
  if(GreaterThan(Var(9),4))    SetVar(4,Mul(Sub(8,Var(9)),4));
  if(Equal(Var(8),DIR_Left())) SetVar(4, Mul(Var(4),-1));
  SetVar(5,Mul(Sum(Var(9),-4),6));
  SetVar(7,Mul(Var(9),22));  
  if(Equal(Var(8),DIR_Left())) SetVar(7,Mul(Var(7),-1));
  SetVar(3,Mul(Var(4),1));
  SetVar(2,Mul(Sum(Var(9),-4),3));
  SetVar(6,20);
  Var(0)=Contents();
  Exit(Var(0),Var(4),Var(5),Var(7),Var(3),Var(2),Var(6));
  ObjectCall(Var(0), "Shot");
  return(1);
