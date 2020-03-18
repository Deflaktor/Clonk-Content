#strict
#include PRNT

local target, jumps;

/* Zufallsflint */
Check:
  SetAction("Delay");
  return(1);
  
Checkit:
  if(target)
    if(!GetAlive(target))
      target=0;
  if(GetOCF() & (OCF_HitSpeed1()|OCF_HitSpeed2()|OCF_HitSpeed3()|OCF_HitSpeed4())) {
    if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) 
      Hit();
  } else
    Explode(20);
  return(1);

/* Aufschlag */
Hit:
  SetAction("Checking");
  Explode(5+Random(20),CreateObject(PRNT));
  if(!target) {
  while(SetVar(0,FindObject(0,0,0,-1,-1,OCF_Living(),0,0,0,Var(0)))) 
    if(CheckHim(Var(0))) {
      target = Var(0);
      break;
    }
  }
  if(target) {
    var angle = Angle(GetX(),GetY(),GetX(target),GetY(target));
    SetXDir(Sin(angle, 30));
    SetYDir(-Cos(angle, 30)-20);
  } else {
    SetYDir(-50);
  }
  jumps++;
  if(jumps>3&&Not(Random(10-jumps))) Explode(20);
  return(1);

CheckHim:
  if (GetOwner()==GetOwner(Par(0)))
    return(0);
  if (!GetAlive(Par(0)))
    return(0);
  return(1);
/*
CalculateSpeed45:
  var x, y, g, precision;
  x = AbsX(GetX(Par(0)));
  y = -AbsY(GetY(Par(0)));
  g = GetGravity()*20;
  precision = 10;
  return(precision*x*Sqrt(Abs( g/(x-y) ))/100);
  
CalculateSpeed60:
  var x, y, g, precision;
  x = AbsX(GetX(Par(0)));
  y = -AbsY(GetY(Par(0)));
  g = GetGravity()*20;
  precision = 10;
  return(precision*x*Sqrt(Abs( g/(5*x-3*y) ))/41);
  
Sqr:
  return(Par(0)*Par(0));
  */
