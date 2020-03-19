/*-- Gunblade --*/

#strict
#include _WOM

SelectionSound:
  Sound("Knife");
  return(1);

ShotSound:
  Sound("KnifeShot");
  return(1);

public isWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon());

public MinRange:
  return(5);

public MaxRange:
  return(300);
  
/* Ammo ID */  
GetAmmoID:
  return(GBK1);

Reloaden:
  if(!Contained())
    return(inherited());
  if(Contained()->Contents()!=this())
    return(inherited());
  if(GetAction() S= "Reload")
    return(inherited());
  if(!(GetAction(Contained()) S= "ArmedWalk"))
    return(inherited());
  Var(1)=GetDir(Contained());
  while(Var(0)=FindObject(0, Var(1)*32-16,-16,16,28,0,0,0,NoContainer(),Var(0)))
    if( ObjectCall(Var(0),"IsProjectile") )
      if( Contained()->GetHostile(Var(0)) ) {
        Repel(Var(0), Var(1));
		SetDir(GetDir(Contained()),CreateObject(GB0E,0,10,-1));
		Sound("SchwertSchwingen");
		Sound("SchwertSchlagen");
		CastObjects(SPRK,1,20);
		break;
      }
  return(inherited());

Repel:
  var speed, yDir;
  speed=Abs(GetXDir(Par(0)));
  if(Par(1)==DIR_Left())
    speed=-speed;
  yDir=GetYDir(Par(0))-5+Random(10);
  SetSpeed(speed,yDir,Par(0));
  if(SEqual(GetAction(Par(0)),"Travel")) {
    SetLocal(0,speed,Par(0));
    SetLocal(1,yDir,Par(0));
    if (Local(0,Par(0))<0) SetDir(DIR_Left(),Par(0));
    else SetDir(DIR_Right(),Par(0));
  }
  SetOwner(GetOwner(Contained()),Par(0));
  return(1);