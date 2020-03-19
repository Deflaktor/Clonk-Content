/*-- Laser --*/

#strict
#include _POV

// Local 0: Fluggeschwindigkeit horizontal

/* Wird abgefeuert, Par(0) ist Schußrichtung */
public Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-100);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+100);
  SetLocal(1,-15+Random(30));
  //SetR(90+Angle(0,0,Local(0),Local(1)));
  SetAction("Travel");
  return(1);
  
/* Fliegt */
private Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-5,-5,10,10))
    return(HitObject(Var(0)));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  return(1);
  
/* Treffer */
protected Hit:
  ObjectCall(CreateObject(EXPL),"Launch",(Dmg()+1)/2);
  //RemoveObject();
  return(1);
    
private HitObject: // C4Object* pObject
  if(GetOwner()==GetOwner(Par(0)))
    return(1);
  Sound("ProjectileHit*");
  DoEnergy(-Dmg(),Par(0));
  DoDamage(Dmg(),Par(0));
  SetXDir(Sum(GetXDir(Par(0)),Div(Local(0),4)),Par(0));
  RemoveObject();
  return(1);

Abgeprallt:
  Sound("Abprallen");
  //SetR(90+Angle(0,0,Local(0),Local(1)));
  Local(2)++;
  if(Local(2)>10) {
    ObjectCall(CreateObject(EXPL),"Launch",4);
    RemoveObject();
  }
  return(1);

ContactTop:
  Local(1) = -Local(1);
  Abgeprallt();
  return(1);
  
ContactBottom:
  Local(1) = -Local(1);
  Abgeprallt();
  return(1);
  
ContactLeft:
  Local(0) = -Local(0);
  Abgeprallt();
  return(1);

ContactRight:
  Local(0) = -Local(0);
  Abgeprallt();
  return(1);

Dmg:
  return(7);
