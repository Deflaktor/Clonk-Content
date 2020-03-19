/*-- Gewehrkugel --*/

#strict
#include _POV

local XDir, YDir, Dir, Counter;

/* Initialisierung */

public Launch:
  if (Par(0) == DIR_Left()) {
    XDir = -25;
    Dir = -1;
  } else {
    XDir = +25;
    Dir = 1;
  }
  YDir = 0;
  SetXDir(XDir);
  SetYDir(YDir);
  SetAction("Flying");
return(1);

protected Hit:
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()/19);
return(1);

protected Flight:
  if (GetActTime() > 45)
    return(RemoveObject());
  SetXDir(XDir);
  SetYDir(YDir);
  if (GetActTime() < 6)
    return(1);
  var target = CheckHit(-8,-15,16,30);
  if (!target) return(1);
  if(GetX(target)>GetX())
    SetXDir(Dir*XDir);
  else
    SetXDir(-Dir*XDir);
  Hit();
return(1);

Dmg:
  return(3*19);