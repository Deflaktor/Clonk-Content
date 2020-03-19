#strict
#include _POV

Dmg: return(4);

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-180);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+180);
  SetAction("Travel");
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(Local(0)/10,-7,Abs(Local(0)/10),14))
    return(HitObject(Var(0)));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
  return(1);
  
/* Treffer */
Hit:
  Sound("BulletHit*", 0, 0, 50);
  CastParticles("PxSpark", 5, 25, 0, 0, 5, 25, RGBa(255, 200, 0, 0), RGBa(255, 255, 0, 100));
  RemoveObject();
  return(1);
    
HitObject:
  Sound("ProjectileHit*");
  DoDamage(Dmg(),Par(0));
  Punch(Par(0),Dmg());
  RemoveObject();
  return(1); 

