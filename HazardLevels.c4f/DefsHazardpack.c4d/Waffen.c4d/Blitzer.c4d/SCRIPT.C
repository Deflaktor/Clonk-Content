#strict
#include _WOM

local lastShotTime, warmUp;

Dmg:
  return(_inherited()*3);
  
DPS:
  if(warmUp<5) return(38*Dmg()/(GetActMapVal("Length", "Reload") * GetActMapVal("Delay", "Reload")));
  else if(warmUp<12) return(38*Dmg()/(GetActMapVal("Length", "Reload2") * GetActMapVal("Delay", "Reload2")));
  else if(warmUp<30) return(38*Dmg()/(GetActMapVal("Length", "Reload3") * GetActMapVal("Delay", "Reload3")));
  return(38*Dmg()/(GetActMapVal("Length", "Reload4") * GetActMapVal("Delay", "Reload4")));
  
GetAmmoID:
  return(LGTS);

SelectionSound:
  Sound("SelectBlitzer");
  return(1);

ShotSound:
  Sound("Electric");
  return(1);

Shot:
  // Blitze abfeuern
  for(var i=0;i<3;i++) {
    var obj = Contents();
	if(!obj) obj=CreateContents(GetAmmoID());
	SetOwner(GetOwner(Contained()), obj);
    Exit(obj, Par(1)*24-12,0,0, 0,0,0 );
    if(Par(1)==DIR_Left())
      obj->Launch(GetX()-10,GetY()-1,1800);
    if(Par(1)==DIR_Right())
      obj->Launch(GetX()+10,GetY()-1,0);
  }
  return(1);
  
  
Fire:
  if(_inherited()) {
    if(FrameCounter()-lastShotTime<100) {
	  warmUp++;
	  if(warmUp==5) Sound("Punch1");
	  if(warmUp==12) Sound("Punch2");
	  if(warmUp==30) Sound("Punch3");
	  if(warmUp==5||warmUp==12||warmUp==30)
	    CastParticles ("LightningSpark",5,60, 0,0, 60,60, RGB(0,100,255), RGB(0,100,255));
	}
	if(warmUp<5) SetAction("Reload");
	else if(warmUp<12) SetAction("Reload2");
	else if(warmUp<30) SetAction("Reload3");
	else SetAction("Reload4");
    reloadTime = GetActMapVal("Length", GetAction()) * GetActMapVal("Delay", GetAction());
    reloading = reloadTime;
	lastShotTime = FrameCounter();
    return(1);
  }
  return(0);

Reloaden:
  if(FrameCounter()-lastShotTime>=100&&warmUp>=5) {
    Sound("DePressurize");
	warmUp=0;
  }
  return(_inherited());
  
IsWeapon:
  return(MiddleRangeWeapon());

public MinRange:
  return(50);

public MaxRange:
  return(250);