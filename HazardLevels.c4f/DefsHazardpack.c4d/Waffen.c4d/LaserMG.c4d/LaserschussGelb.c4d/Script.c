/*-- Laser --*/

#strict
#include _POV

// Local 0: Fluggeschwindigkeit horizontal

/* Wird abgefeuert, Par(0) ist Schußrichtung */
public Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-100);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+100);
  SetLocal(2,GetY());
  if(Random(2))
    Local(1) = 180;
  else
    Local(1) = 0;
  SetAction("Travel");
  return(1);
  
/* Fliegt */
private Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-5,-5,10,10))
    return(HitObject(Var(0)));
  // Bewegung
  SetPosition(GetX()+Local(0)/10,Local(2)+Sin(Local(1),10));
  SetXDir(0);
  SetYDir(0);
  Local(1)+=45;
  if(GetX()<0||GetX()>LandscapeWidth())
    RemoveObject();
  return(1);

/* Treffer */
protected Hit:
  //ObjectCall(CreateObject(EXPL),"Launch",4);
  //RemoveObject();
  return(1);
    
private HitObject: // C4Object* pObject
  Sound("ProjectileHit*");
  DoEnergy(-Dmg(),Par(0));
  DoDamage(Dmg()/2,Par(0));
  SetXDir(Sum(GetXDir(Par(0)),Div(Local(0),4)),Par(0));
  RemoveObject();
  return(1);
  
Dmg:
  return(2);