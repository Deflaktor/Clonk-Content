#strict
#include _POV

/* Wird abgefeuert, Par(0) ist Schußrichtung, Par(1) gibt an, Ob Schuß besonders schnell sein soll */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-30);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+30);
  SetAction("Travel");
  SetPhase(4);
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(CheckHit(-5,-5,10,10))
    return(Hit());
  if(GBackSolid()) return(Hit());
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
  // Je nach Phase kommt Flare
  if(Equal(GetPhase(),5)) // Phase 0
    CreateObject(_FLR,0,0,-1);
  if(Or(Equal(GetPhase(),1),Equal(GetPhase(),4))) // Phase 1 oder 4
    And(CreateObject(_FLR,0,-2,-1),CreateObject(_FLR,0,+2,-1));
  if(Or(Equal(GetPhase(),2),Equal(GetPhase(),3))) // Phase 2 oder 3
    And(CreateObject(_FLR,0,-3,-1),CreateObject(_FLR,0,+3,-1));
  return(1);
  
/* Treffer */
Hit:
  CreateObject(_FLF,0,0,GetOwner())->Launch();
  RemoveObject();
  return(1);
