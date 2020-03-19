#strict
#include _POV

/*-- Disruptorschuss --*/

Dmg:
  return(DirectHitDamage()+DefinitionCall(_PUL,"Dmg")*24);

DirectHitDamage:
  return(30);
  
// Local 0: Fluggeschwindigkeit horizontal

/* Wird abgefeuert, Par(0) ist Schußrichtung */
public Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-50);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+50);
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
  // Flare
  if(Equal(Local(0),-50)) SetVar(0,CreateObject(CKFL,-4,9,-1));
  if(Equal(Local(0),+50)) SetVar(0,CreateObject(CKFL,+4,9,-1));
  SetPhase(Random(4),Var(0));
  return(1);

HitObject:
  DoEnergy(-DirectHitDamage(),Par(0));
  Hit();
  return(1);
  
/* Treffer */
Hit:
/*  if(Par(0))
    if(GetOCF(Par(0)) & OCF_CrewMember()) {
      if(GetEnergy(Par(0))<=100)
        ObjectCall(Par(0),"Platzen");
    }*/
  while(LessThan(Var(),361)) And(SetR(Var(),CreateObject(_PUL,0,0,GetOwner(this()))),SetVar(0,Sum(Var(),15)));
  RemoveObject();
  return(1);
    