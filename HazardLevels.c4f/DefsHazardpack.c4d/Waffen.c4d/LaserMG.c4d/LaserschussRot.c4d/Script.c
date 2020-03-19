/*-- Laser --*/

#strict
#include _POV

// Local 0: Fluggeschwindigkeit horizontal

/* Wird abgefeuert, Par(0) ist Schußrichtung */
public Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-100);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+100);
  SetLocal(1,-15+Random(30));

    Var(1) = CreateObject(GetID(),0,0,GetOwner());
    ObjectSetAction(Var(1), "Travel");
    SetLocal(0,Local(0),Var(1));
    SetLocal(1,Local(1)-15+Random(40),Var(1));
    Var(1) = CreateObject(GetID(),0,0,GetOwner());
    ObjectSetAction(Var(1), "Travel");
    SetLocal(0,Local(0),Var(1));
    SetLocal(1,Local(1)+15-Random(40),Var(1));
    Var(1) = CreateObject(GetID(),0,0,GetOwner());
    ObjectSetAction(Var(1), "Travel");
    SetLocal(0,Local(0),Var(1));
    SetLocal(1,Local(1)-15-Random(40),Var(1));
    Var(1) = CreateObject(GetID(),0,0,GetOwner());
    ObjectSetAction(Var(1), "Travel");
    SetLocal(0,Local(0),Var(1));
    SetLocal(1,Local(1)-15+Random(40),Var(1));


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
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()+1);
  RemoveObject();
  return(1);
    
private HitObject: // C4Object* pObject
  Sound("ProjectileHit*");
  DoEnergy(-Dmg(),Par(0));
  DoDamage(Dmg(),Par(0));
  SetXDir(Sum(GetXDir(Par(0)),Div(Local(0),16)),Par(0));
  RemoveObject();
  return(1);
  
Dmg: return(1);