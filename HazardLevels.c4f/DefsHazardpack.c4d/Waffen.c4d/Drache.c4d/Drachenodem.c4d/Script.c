#strict
#include _POV

Dmg:
  return(25);
  
/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch: 
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-100);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+100);
  SetAction("Travel");
  SetDir(Par(0));
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-17,-6,34,12))
    return(Hit());
  // Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  CreateParticle("PxSpark", 0, -2+Random(4), 0, 0,60,RGBa(200+Random(56),Random(51),0,Random(129)));
  return(1);

/* Treffer */
Hit:
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()+5);
  RemoveObject();
  return(1);
  
