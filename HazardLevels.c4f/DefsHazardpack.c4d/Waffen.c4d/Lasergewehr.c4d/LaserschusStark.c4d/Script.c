/*-- Laser --*/

#strict
#include _POV

// Local 0: XDir
// Local 1: YDir

/* Wird abgefeuert */
public Launch:  
  // Schußrichtung
  SetLocal(0,Div(Par(0),5));
  SetLocal(1,Div(Par(1),5));
  SetAction("Travel");
  // Sicht verfolgen
  SetPlrView(GetOwner(),this());
  return(1);
  
/* Fliegt */
private Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-5,-5,10,10))
    return(HitObject(Var(0)));
  // Zielsuche
  Var(0)=SearchTarget();
  // Sound falls neues Ziel
  if(Var(0)!=Local(2))
    Sound("Bip");
  Local(2)=Var(0);
  // Ziel ansteuern
  if (Local(2)) TargetControl();
  // Ungesteuerte Bewegung
  // Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  return(1);
  
  
/* Treffer */
public Hit:
  RemoveObject();
  return(1);

private HitObject: // C4Object* pObject
  Sound("ProjectileHit*");
  CreateObject(_SIE)->SetAction("Blow",Par(0));
  SetXDir(Sum(GetXDir(Par(0)),Div(Local(0),2)),Par(0));
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
  Local(0) = Local(0) * 3 / 5 + Sin(GetR(),40) / 5;
  Local(1) = Local(1) * 3 / 5 - Cos(GetR(),40) / 5;
  return(1);
  
/* Eintritt */
protected Entrance:
  if (Equal(GetAction(),"Travel")) Hit();
  return();