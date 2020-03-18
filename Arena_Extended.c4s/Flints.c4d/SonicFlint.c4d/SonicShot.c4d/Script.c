#strict

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  

  SetLocal(0,Par(0));
  SetLocal(1,Par(1));
  SetLocal(2,Par(3)-1);
  
  SetR(Par(2));
  
  SetDir(DIR_Right());

  SetAction("Travel");
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if (SetVar(0,FindObject(0,-5,-5,10,10,OCF_Prey(),0,0,NoContainer()))) return(SonicHit(Var(0)));
  if (SetVar(0,FindObject(0,1,0,0,0,OCF_Prey(),0,0,NoContainer()))) return(SonicHit(Var(0)));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  if(GreaterThan(GetActTime(),20*Local(2))) RemoveObject();
  return(1);
  
/* Treffer */
Hit:
  RemoveObject();
  Sound("Thump1");
  return(1);
    
SonicHit:
  DoEnergy(-5,Par(0));
  Fling(Par(0),Sub(Random(20),10),Sub(-2,Random(5)));
  RemoveObject();
  Sound("Thump1");
  return(1); 