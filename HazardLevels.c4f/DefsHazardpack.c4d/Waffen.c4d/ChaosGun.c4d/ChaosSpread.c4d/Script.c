#strict
#include _POV


local angle, targetAngle;

Dmg:
  return(DefinitionCall(_PUL,"Dmg")*5);

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-50);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+50);
  SetAction("Travel");
  angle = Angle(0,0,Local(0),0);
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(CheckHit(-5,-5,10,10))
    return(Hit());
  Local(2)=SearchTarget();
  if (Local(2))
    TargetControl();
  // Bewegung
  SetXDir(Local(0)+Random(60)-30);
  SetYDir(Local(1)+Random(55)-30);
  return(1);
  
/* Treffer */
Hit:
  Var(1)=5;
  while(Var(0)<=360) {
    Var(2) = CreateObject(_PUL,0,0,GetOwner());
    SetLocal(1, 5, Var(2));
    SetR(Var(0), Var(2));
    Var(0) += 360/Var(1);
  }
  RemoveObject();
  return(1);
    
/* Steuerung zum Zielobjekt */
private TargetControl:
  // Ziel anpeilen
  targetAngle = Angle( GetX(),GetY(),GetX(Local(2)),GetY(Local(2)) );
  
  //if((targetAngle-angle+360) % 360 > 20 || (angle-targetAngle+360) % 360 > 20)
  //  angle = (angle + angleDir + 360) % 360;
  //else
  //  angle = (angle - angleDir + 360) % 360;

  if(targetAngle + 360>angle + 360)
    angle += 5;
  else
    angle -= 5;

  if(angle<0)
    angle+=360;
  if(angle>360)
    angle-=360;

  // SetR( Angle(GetX(),GetY(),GetX(Local(2)),GetY(Local(2))) );
  // Geschwindigkeitskontrolle  
  Local(0) = Local(0) * 3 / 4 + Sin(angle,50) * 1 / 4;
  Local(1) = Local(1) * 3 / 4 - Cos(angle,50) * 1 / 4;
  return(1);
