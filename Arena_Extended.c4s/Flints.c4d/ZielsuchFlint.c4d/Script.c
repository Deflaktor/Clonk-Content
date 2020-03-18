#strict
#include PRNT

Initialize:
  SetAction("SetColor");
  return(1);

SetMyColor:
  if(GetOwner()==-1)
    SetColorDw(RGBa(255, 255, 255, 0));
  return(1);

Departure:
  SetAction("Delay");
  return(1);

NoShiftOwner:
  return(!(GetAction() S= "Idle"));

Checkit:
  SetLocal(4, Sqrt(GetXDir()*GetXDir()+GetYDir()*GetYDir()) );
  Var(1)=10;
  while(SetVar(0,FindObject(0,0,0,-1,-1,OCF_Living(),0,0,0,Var(0)))) if(Var(1)) {
    CreateSplitter(Var(0));
    Var(1)--;
  }
  return(RemoveObject());

Targetit:
  if(!Local(0))
    if(SetVar(0,FindObject(0,0,0,-1,-1,OCF_Living(),0,0,0,Var(0))))
      CheckZiel(Var(0));
  if(Local(0))
    CheckSog(Local(0));
  else
    SetSpeed();
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) Hit();
  if(GreaterThan(GetActTime(this()),700)) return(RemoveObject());
  return(1);

Hit:
  SetVar(0,CreateObject(_QNE,0,20,GetOwner()));
  ObjectCall(Var(0),"Start",Local(0),Local(1));
  Explode(50);
  return(1);

Entrance:
  if(GetAction() S= "Target")
    return(0);
  SetOwner(GetOwner(Par(0)),this());
  return(1);

CreateSplitter:
//if (!PathFree(GetX(),GetY(),GetX(Par(0)),GetY(Par(0))))
//return(1);
if (GetOwner()==GetOwner(Par(0)))
return(1);
if (!GetAlive(Par(0)))
return(1);
SetVar(0,CreateObject(GetID()));
ObjectSetAction(Var(0),"Target");
SetOwner(GetOwner(),Var(0));
ObjectCall(Var(0), "SetMyColor");
SetLocal(0,Par(0),Var(0));
SetLocal(4,Local(4),Var(0));
return(0);

CheckSog:
if (!GetAlive(Par(0)))
return(SetLocal());
/*if (!PathFree(GetX(),GetY(),GetX(Par(0)),GetY(Par(0))))
{
SetSpeed();
return(1);
}*/
//if (BitAnd(OCF_CrewMember(),GetOCF(Par(0))))
SetVar(1,Div(Sub(GetX(),GetX(Par(0))),-2));
SetVar(2,Div(Sub(GetY(),GetY(Par(0))),-2));
SetVar(1, -GetX()+GetX(Par(0)) );
SetVar(2, -GetY()+GetY(Par(0)) );
SetVar(3, Angle(GetX(),GetY(),GetX(Par(0)),GetY(Par(0))) );
//SetVar(3, Var(3)-25+Random(50));
SetLocal(3, Local(3) + Var(3)-Local(3));
SetLocal(1, Sin(Local(3),Local(4)));
SetLocal(2, -Cos(Local(3),Local(4)));
SetVar(1, Local(1));
SetVar(2, Local(2));
if (GetXDir()>0)
SetComDir(COMD_Right());
if (GetXDir()<0)
SetComDir(COMD_Left());
SetSpeed(Var(1),Var(2));
return(0);

CheckZiel:
if (!PathFree(GetX(),GetY(),GetX(Par(0)),GetY(Par(0))))
return(1);
if (GetOwner()==GetOwner(Par(0)))
return(1);
if (!GetAlive(Par(0)))
return(1);
SetLocal(0,Par(0));
return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);