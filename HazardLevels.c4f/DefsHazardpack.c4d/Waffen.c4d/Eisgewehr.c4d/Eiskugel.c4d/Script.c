#strict
#include _POV

Dmg:
  return(0);

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-130);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+130);
  SetAction("Travel");
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-8,-8,16,16)) return(Ice(Var(0)));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
  CreateObject(_EGF,0,0,-1);
  CreateObject(_EGF,0,-1,-1);
  CreateObject(_EGF,0,1,-1);
  return(1);
  
/* Treffer */

Ice:
  Sound("freeze");
  ObjectSetAction(Par(0),"Frozen");
  RemoveObject();
  return(1);

Hit:
  RemoveObject();
  return(1);