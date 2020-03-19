#strict
#include _POV

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-80);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+80);
  SetAction("Travel");
  SetDir(Par(0));
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-5,-5,10,10))
    return(Hit(Var(0)));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
  return(1);
  
/* Treffer */

	Hit:
CreateObject(EGRE);
RemoveObject();
return(1);
    
SonicHit:
CreateObject(EGRE);
RemoveObject();
return(1);
