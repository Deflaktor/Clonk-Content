#strict
#include KI58

ShotLeft:
  SetDir(DIR_Left());
  Var(0)=CreateContents(GameCall("Zufallsflint"));
  SetOwner(GetOwner(),Var(0));
  Exit(Var(0),-8,-1,0,-8,0,0);
  ObjectCall(Var(0),"Check");
  SetComDir(COMD_Stop());
  return(1);

ShotRight:
  SetDir(DIR_Right());
  Var(0)=CreateContents(GameCall("Zufallsflint"));
  SetOwner(GetOwner(),Var(0));
  Exit(Var(0),+8,-2,0,+8,0,0);
  ObjectCall(Var(0),"Check");
  SetComDir(COMD_Stop());
  return(1);
