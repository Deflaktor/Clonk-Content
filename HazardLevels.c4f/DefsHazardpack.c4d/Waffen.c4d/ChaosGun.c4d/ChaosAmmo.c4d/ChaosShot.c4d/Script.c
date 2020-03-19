#strict
#include _POV

Dmg: return(4);

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-100);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+100);
  SetAction("Travel");
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-5,-5,10,10))
    return(Hit(Var(0)));
  // Bewegung
  SetXDir(Local(0)+Random(60)-30);
  SetYDir(Local(1)+Random(60)-30);
  return(1);
  
/* Treffer */
Hit:
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()*2);
  //if(Var(0)) DoEnergy(-Dmg()/2,Var(0));
  RemoveObject();
  return(1);
    