/*-- Laserschuss --*/

#strict

IsProjectile:
  return(1);

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-100);
   if (Equal(Par(0),DIR_Right())) SetLocal(0,+100);
  SetAction("Travel");
 return(1);
  
/* Fliegt */
Travel:
/* Treffer-Überprüfung */

// Normaler Einschlag:
  if (Or(FindObject(0,-5,-5,10,10,OCF_Prey(),0,0,NoContainer()),
         FindObject(0,1,0,0,0,OCF_Prey(),0,0,NoContainer()))) return(Hit());

// Bewegung:
  SetXDir(Local(0));
  SetYDir(+5);
  CreateObject(_FLR,0,0,-1);
 return(1);
  
/* Treffer */
Hit:
  ObjectCall(CreateObject(EXPL),"Launch",13);
  RemoveObject();
 return(1);