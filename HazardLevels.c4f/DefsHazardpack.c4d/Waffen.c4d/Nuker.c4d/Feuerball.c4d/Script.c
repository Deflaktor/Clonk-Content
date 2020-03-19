#strict
#include _POV


/* Wird abgefeuert, Par(0) ist Schußrichtung */

Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-60);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+60);
  // Flare
  while(LessThan(Var(),361)) And(SetR(Var(),CreateObject(PUL2,Var(1)*5,2,GetOwner(this()))),SetVar(0,Sum(Var(),15)));
  SetAction("Travel");
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
  CreateParticle("PxSpark", Local(0)/-4, -6+Random(12), Local(0)/-12, 0,150,RGBa(200+Random(56),Random(51),0,Random(129)));
  if(Var(1)=CheckHit(-16,-16,32,32))
    SonicHit(Var(1));
  while(SetVar(0,FindObject(0,-64+Local(0),-64,128+Local(0),128,0,0,0,NoContainer(),Var(0)))) SonicHit2(Var(0));
  return(1);
  
Hit:
  CreateObject(_NRE);
  return(RemoveObject());

SonicHit:
  Sound("Gelhit");
  ObjectCall(Par(0),"Bluten",60);
  DoEnergy(-Dmg(),Par(0));
  return(1); 

SonicHit2:
  // DoDamage(Dmg(),Par(0));
  return(1); 
  
Dmg:
  return(1000);