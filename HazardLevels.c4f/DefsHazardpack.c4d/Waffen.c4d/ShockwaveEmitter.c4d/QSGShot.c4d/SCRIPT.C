#strict
#include _POV

/* Wird abgefeuert, Par(0) ist Schußrichtung, Par(1) gibt an, Ob Schuß besonders schnell sein soll */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-200);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+200);
  SetAction("Travel");
  SetPhase(4);
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(GetActTime()>2)
  if(CheckHit(-30,-20,60,40))
    return(Hit());
  if(GBackSolid()) return(Hit());
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
  // Je nach Phase kommt Flare
  CreateObject(CKF5,0,8,-1);
  return(1);
  
/* Treffer */
Hit:
  CreateObject(_SLC,0,32);
  RemoveObject();
  return(1);
