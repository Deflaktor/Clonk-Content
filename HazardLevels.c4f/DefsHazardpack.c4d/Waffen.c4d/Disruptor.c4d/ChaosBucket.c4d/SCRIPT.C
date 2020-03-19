#strict
#include _POV

/*-- Disruptorschuss --*/

Dmg:
  return(DirectHitDamage()+DefinitionCall(_AM7,"Dmg")*12);

DirectHitDamage:
  return(25);

// Local 0: Fluggeschwindigkeit horizontal

/* Wird abgefeuert, Par(0) ist Schußrichtung */
public Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-80);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+80);
  SetAction("Travel");
  SetDir(Par(0));
  return(1);
  
/* Fliegt */
private Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-5,-5,10,10))
    return(HitObject(Var(0)));
  if(GBackSolid()) return(Hit());
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
  return(1);

HitObject:
  DoEnergy(-DirectHitDamage(),Par(0));
  Hit();
  return(1);
  
/* Treffer */
Hit:
  while(Var(0)<=360) {
    Var(1) = CreateObject(_AM7,Sin(Var(0),7),-Cos(Var(0),7),GetOwner());
    ObjectSetAction(Var(1), "Travel");
    SetLocal(0,Sin(Var(0),100),Var(1));
    SetLocal(1,-Cos(Var(0),100),Var(1));
    Var(0)+=30;
  }
  RemoveObject();
  return(1);
    