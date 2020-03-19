#strict
#include _HAC

CheckArea:
  // Clonk unter der Klappe suchen
  SetVar(0,FindObject(0, -12,10,24,20, OCF_CrewMember()));
  // Automatisch öffnen
  if (Var(0)) ControlUp();
  return(1);
  
// Stellt SolidMask wieder her
PutSolidMask:
  SetSolidMask(5,19,22,2,5,19);
  return(1);
        
  