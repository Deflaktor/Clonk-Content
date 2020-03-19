#strict
#include _POV

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-80);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+80);
  SetAction("Travel");
  SetDir(Par(0));
  return(1);
  
/* FX */
Effect:
  ObjectCall(CreateObject(FXPW,1,1),"Activate",this(),4);
  return(1);

/* Fliegt */
Travel:
  // Treffer-Überprüfung
  while(SetVar(0,FindObject(0, -80,-80,160,160,OCF_Alive(),0,0,NoContainer(),Var(0)))) if(GetHostile(Var(0))) SogHit(Var(0));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
  return(1);
  
/* Treffer */
Hit:
  while(SetVar(0,FindObject(0,-200,-200,400,400,OCF_Alive(),0,0,NoContainer(),Var(0)))) if(GetHostile(Var(0))) SonicHit(Var(0));
  SetVar(0,0);
  while(SetVar(0,FindObject(0,-200,-200,400,400,0,0,0,NoContainer(),Var(0)))) if(GetHostile(Var(0))) DoDamage(1,Var(0));
  RemoveObject();
  Sound("Thump1");
  return(1);

SogHit:
  SetVar(1,Sub(GetX(),GetX(Par(0)))+Local(0)/2);
  SetVar(2,Sub(GetY(),GetY(Par(0))));
  DoEnergy(-2,Par(0));
  Fling(Par(0),0,-10);
  SetSpeed(Var(1)*(1+Random(5)),Var(2)*(1+Random(5))-20,Par(0));
  //Fling(Par(0),Get,-4-Random(10));
  return(1); 

SonicHit:
  DoEnergy(-5,Par(0));
  Fling(Par(0),Random(4)-2,-4-Random(10));
  return(1); 