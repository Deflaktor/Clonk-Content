#strict
#include _POV

Damage:
  return(0);

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-30);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+30);
  SetAction("Travel");
  return(1);
  
/* Fliegt */
Travel:
  // Vergiften
  while(Var(0)=FindObject(0, -20,-20,40,40,OCF_Prey(),0,0,NoContainer(),Var(0)))
    if(GetTarget(Var(0))&&!(GetActTime()%4))
      Poison(Var(0));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  if (GetActTime() > 5)
    CreateParticle("Smoke", 0,10, Local(0),Local(1), 150+Random(50), RGBa(0,255,0,0));
  if (GetActTime() > 20)
    return(Hit());
  return(1);
  
Poison:
  Var(0)=CreateObject(_SIE);
  Var(0)->SetAction("Harm",Par(0));
  SetLocal(1,6,Var(0));
  SetLocal(2,RGBa(0,255,0,0),Var(0));
  return(1);
  
/* Treffer */
Hit:
  RemoveObject();
  return(1);
    
