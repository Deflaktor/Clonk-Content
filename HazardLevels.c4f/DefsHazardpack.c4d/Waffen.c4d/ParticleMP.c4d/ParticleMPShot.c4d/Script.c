#strict
#include _POV

/*-- Partikel--*/

// Local 0: Fluggeschwindigkeit horizontal

/* Wird abgefeuert, Par(0) ist Schußrichtung */
public Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-150);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+150);
  SetVar(0,Random(2));
  if (Var(0)) SetLocal(1,Random(15));
  if (Not(Var(0))) SetLocal(1,Mul(Random(15),-1));
  if(Par(2))
    SetLocal(1,Par(2));
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
  SetVar(1,CreateObject(FXPG,0,32));
  ObjectSetAction(Var(1),"Blast");
  RemoveObject();
  return(1);
    
private HitObject: // C4Object* pObject
  Sound("ProjectileHit*");
  //DoEnergy(Sub(0,Sum(1,Random(4))),Par(0));
  //DoDamage(Sum(1,Random(4)),Par(0));
  DoEnergy(-DirectHitDamage(),Par(0));
  SetXDir(Sum(GetXDir(Par(0)),Div(Local(0),10)),Par(0));
  SetVar(1,CreateObject(FXPG,0,32));
  ObjectSetAction(Var(1),"Blast");
  RemoveObject();
  return(1);

Dmg:
  return(DirectHitDamage()+DefinitionCall(FXPG,"Dmg"));

DirectHitDamage:
  return(1);