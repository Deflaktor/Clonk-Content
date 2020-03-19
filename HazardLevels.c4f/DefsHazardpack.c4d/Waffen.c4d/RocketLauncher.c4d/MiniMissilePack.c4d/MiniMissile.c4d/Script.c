/*-- Mini-Rakete --*/

#strict
#include _POV

Dmg: return(10);

// Local 0: XDir
// Local 1: YDir
local maxSpeed, angle, speed;

/* Status */
public IsMissile: return(1);

/* Wird abgefeuert */
public Launch:  
  // Schußrichtung
  SetLocal(0,Par(0));
  SetLocal(1,Par(1));
  maxSpeed = Distance(0,0,Par(0),Par(1));
  angle = Angle(0,0,Par(0),Par(1));
  speed = maxSpeed / 10;
  SetAction("Travel");
  // Sicht verfolgen
  SetPlrView(GetOwner(),this());
  return(1);
  
/* Fliegt */
private Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-5,-5,10,10))
    return(Hit(Var(0)));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  SpeedUp();
  Smoke( 0, 0, 5 );
  return(1);

SpeedUp:
  speed += 1+Max(0,(maxSpeed-speed)/20);
  Local(0) = Sin(angle,speed);
  Local(1) = -Cos(angle,speed);
  return(1);
  
/* Treffer */
public Hit:
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()/2+speed/10);
  RemoveObject();
  return(1);

