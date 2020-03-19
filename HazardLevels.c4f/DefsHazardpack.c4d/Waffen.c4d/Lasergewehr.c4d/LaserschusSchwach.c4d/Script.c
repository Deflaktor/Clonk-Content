/*-- Laser --*/

#strict
#include _POV

// Local 0: XDir
// Local 1: YDir
local angle, speed;

/* Wird abgefeuert */
public Launch:  
  // Schußrichtung
  SetLocal(0,Par(0));
  SetLocal(1,Par(1));
  speed = 2*Distance(0,0,Par(0),Par(1));
  angle = Angle(0,0,Par(0),Par(1));
  SetAction("Travel");
  // Sicht verfolgen
  SetPlrView(GetOwner(),this());
  return(1);
  
/* Fliegt */
private Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-5,-5,10,10))
    return(HitObject(Var(0)));
  SpeedDown();
  SetSpeedAndColor();
  return(1);

GetColorFromSpeed:
  return(BoundBy(speed,0,255));

SetSpeedAndColor:
  // Bewegung
  SetXDir(Local(0),0,1000);
  SetYDir(Local(1),0,1000);
  SetObjectBlitMode(6);
  SetClrModulation(RGB(GetColorFromSpeed(), GetColorFromSpeed(), GetColorFromSpeed()));
  // Flare
  var alpha;
  if(speed>230)
    alpha = 255;
  else if(speed>220)
    alpha = 188;
  else if(speed>210)
    alpha = 139;
  else if(speed>200)
    alpha = 103;
  else if(speed>190)
    alpha = 76;
  else if(speed>180)
    alpha = 56;
  else if(speed>170)
    alpha = 41;
  else if(speed>160)
    alpha = 30;
  else if(speed>150)
    alpha = 22;
  else 
    alpha = speed/10;
  CreateParticle("PxSpark", 0, 0, 2*GetXDir()/3, 2*GetYDir()/3,30,RGBa(200+Random(56),GetColorFromSpeed(),0,255-2*alpha/3));
  return(1);

SpeedDown:
  speed -= Max(1,speed/20);
  Local(0) = Sin(angle,speed*100);
  Local(1) = -Cos(angle,speed*100);
  if(speed < 20)
    RemoveObject();
  return(1);
  

/* Treffer */
public Hit:
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()/2);
  RemoveObject();
  return(1);

private HitObject: // C4Object* pObject
  Sound("ProjectileHit*");
  //if(GetOCF(Par(0)) & OCF_CrewMember())
  //  DoEnergy(-Dmg()/2,Par(0));
  DoEnergy(-Dmg()+speed/40,Par(0));
  DoDamage(Dmg()+speed/40,Par(0));
  ObjectSetAction(Par(0),"Jump");
  SetXDir(GetXDir(Par(0))+GetXDir()/4,Par(0));
  SetYDir(GetYDir(Par(0))-30+GetYDir()/4,Par(0));
  RemoveObject();
  return(1);

/* Eintritt */
protected Entrance:
  if (Equal(GetAction(),"Travel")) Hit();
  return();
  
Dmg: return(16);