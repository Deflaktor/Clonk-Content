/* Homing Missile */
#strict
#include _POV

Dmg: return(5*4);

// Local 0: XDir
// Local 1: YDir
// Local 2: Target
local speed;

/* Status */
public IsMissile: return(1);

/* Wird abgefeuert */
public Launch:  
  // Schußrichtung (reduziert)
  var angle, spd, xspd, yspd;
  spd = Distance(0,0,Par(0),Par(1));
  if(!Par(4))
    spd = spd / 4;
  angle = Angle(0,0,Par(0),Par(1));
  xspd = Sin(angle,spd);
  yspd = -Cos(angle,spd);
  speed = spd;

  SetLocal(0, xspd );
  SetLocal(1, yspd );
  SetAction("Travel");
  // Sicht verfolgen
  SetPlrView(GetOwner(),this());
  return(1);
  
/* Fliegt */
private Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-5,-5,10,10))
    return(Hit(Var(0)));
  // Effekte
  if (Not(Random(3))) Smoke( 0, 0, 5 );
  // Zielsuche
  Var(0)=SearchTarget();
  // Sound falls neues Ziel
  if(Var(0)!=Local(2))
    Sound("Bip");
  Local(2)=Var(0);
  // Ziel ansteuern
  if (Local(2)&&!Local(3)) {
    var angle;
    angle = Angle(0,0,Local(0),Local(1));
    angle -= 23;
    for(var i = 1; i<=4; i++) {
      var xspd, yspd;
      xspd = Sin(angle,speed);
      yspd = -Cos(angle,speed);
      Var(0) = CreateObject(GetID());
      SetR(angle, Var(0));
      SetLocal(3,1,Var(0));
      ObjectCall(Var(0), "Launch", xspd, yspd, 0, 0, 1);
      angle += 15;
    }
    return(RemoveObject());
  }
  if (Local(2))
    TargetControl();
  // Ungesteuerte Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  return(1);
  
/* Treffer */
public Hit:
  ObjectCall(CreateObject(EXPL),"Launch",(Dmg()/4)*2+2);
  RemoveObject();
  return(1);

/* Steuerung zum Zielobjekt */
private TargetControl:
  // Ziel anpeilen
  SetR( Angle(GetX(),GetY(),GetX(Local(2)),GetY(Local(2))) );
  // Geschwindigkeitskontrolle  
  //Local(0) = Local(0) * 3 / 4 + Sin(GetR(),speed) / 4;
  //Local(1) = Local(1) * 3 / 4 - Cos(GetR(),speed) / 4;
  //for(var i = 1; i<=2; i++) {
    SetLocal(0,BoundBy(Local(0)+Sin(GetR(),5),-speed,speed));
    SetLocal(1,BoundBy(Local(1)-Cos(GetR(),5),-speed,speed));
  //}
  return(1);
