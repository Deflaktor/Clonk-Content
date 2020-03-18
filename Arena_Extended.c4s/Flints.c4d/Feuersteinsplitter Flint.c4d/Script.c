#strict
#include PRNT

Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

Hit:
  CastObjects(FLNT,10,300);
  Explode(18);
  return(1);

Shot:
  var angle, speed;
  speed = Distance(0,0,GetXDir(),GetYDir());
  angle = Angle(0,0,GetXDir(),GetYDir());
  angle -= 7;
  for(var i = 1; i<=15; i++) {
    var xspd, yspd;
    xspd = Sin(angle,speed);
    yspd = -Cos(angle,speed);
    Var(0) = CreateObject(FLNT, 2 - Random(4), 2 - Random(4), GetOwner());
    SetR(angle, Var(0));
    SetSpeed(xspd, yspd, Var(0));
    angle += 1;
  }
  RemoveObject();
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);
