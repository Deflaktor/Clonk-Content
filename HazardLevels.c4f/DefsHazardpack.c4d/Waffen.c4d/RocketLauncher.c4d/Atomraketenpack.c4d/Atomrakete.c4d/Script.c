/* Homing Missile */
#strict
#include _POV

Dmg: return(110);

// Local 0: XDir
// Local 1: YDir
// Local 2: Target


/* Wird abgefeuert */
Launch:  
  // Schußrichtung (reduziert)
  SetLocal(0, Div(Par(0),3) );
  SetLocal(1, Div(Par(1),3) );
  SetAction("Travel");
  // Sicht verfolgen
  SetPlrView(GetOwner(),this());
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(CheckHit(-5,-5,10,10))
    return(Hit());
  // Effekte
  if (Not(Random(3))) Smoke( 0, 0, 5 );
  // Zielsuche
  Var(0)=SearchTarget();
  // Sound falls neues Ziel
  if(Var(0)!=Local(2))
    Sound("Bip");
  Local(2)=Var(0);
  // Ziel ansteuern
  if (Local(2)) TargetControl();
  // Ungesteuerte Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  return(1);
  
/* Treffer */
Hit:
  ObjectCall(CreateObject(EXPL),"Launch",70);
  ObjectCall(CreateObject(EXPL),"Launch",60);
  RemoveObject();
  return(1);

/* Steuerung zum Zielobjekt */
TargetControl:
  // Ziel anpeilen
  SetR( Angle(GetX(),GetY(),GetX(Local(2)),GetY(Local(2))) );
  // Geschwindigkeitskontrolle  
  //SetLocal(0,BoundBy(Sum( Local(0), Sin(GetR(),5) ),-40,40));
  //SetLocal(1,BoundBy(Sub( Local(1), Cos(GetR(),7) ),-40,40));

  SetR( Angle(GetX(),GetY(),GetX(Local(2)),GetY(Local(2))) );
  // Geschwindigkeitskontrolle  
  Local(0) = Local(0) * 3 / 4 + Sin(GetR(),40) / 4;
  Local(1) = Local(1) * 3 / 4 - Cos(GetR(),40) / 4;
  return(1);