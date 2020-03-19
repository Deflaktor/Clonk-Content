/*-- Gewehrkugel --*/

#strict
#include _POV

Dmg: return(DefinitionCall(_SIE, "Dmg", 1));

local XDir, YDir;

/* Initialisierung */

public Launch:
  if (Par(0) == DIR_Left()) XDir = -125;
  else (XDir = +125);
  YDir = 0;
  SetXDir(XDir);
  SetYDir(YDir);
  SetAction("Flying");
return(1);

protected Hit:
  Smoke(0,0,8);
  RemoveObject();
return(1);

protected Flight:
  if (GetActTime() > 25)
    return(Hit());
  var target = CheckHit(-16,-20,32,40);
  SetXDir(XDir);
  SetYDir(YDir);
  if (!target) return(1);  
  Sound("Crunch");
  CreateObject(_SIE)->SetAction("Harm",target);
  DoDamage(1,target);
  RemoveObject();  
return(1);
