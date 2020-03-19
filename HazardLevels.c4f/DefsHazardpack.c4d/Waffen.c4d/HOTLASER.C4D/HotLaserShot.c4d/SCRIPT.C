#strict
#include _POV

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-20);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+20);
  SetAction("Travel");
  return(1);
  
/* Fliegt */
Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-10,-10,20,20))
    return(HitEnemy(Var(0)));
  while(Var(0)=FindObject(0,-10,-10,20,20,0,0,0,NoContainer(),Var(0))) if(Inflameable(Var(0))) Incinerate(Var(0));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
  CreateObject(_FR2,0,+1,-1);
  return(1);
  
/* Treffer */
HitEnemy:
  if(!Inflameable(Par(0)))
    return(Hit());
  ObjectSetAction(CreateObject(_ETG,0,0,-1),"EternalFlame",Par(0));
  Incinerate(Par(0));
  Sound("Inflame");
  Hit();
  return(1);
Hit:
  for(var angle=0; angle<360; angle+=1152/GetIncinerateRadius()) { 
    CreateParticle("MSpark2", Sin(angle, GetIncinerateRadius()), Cos(angle, GetIncinerateRadius()),0,0,50, RGBa(250,100,100,50));
  }
  Sound("Hot");
  while(Var(0)=FindObject(0,-GetIncinerateRadius(),-GetIncinerateRadius(),GetIncinerateRadius()*2,GetIncinerateRadius()*2,0,0,0,NoContainer(),Var(0))) 
    if(ObjectDistance(Var(0))<=GetIncinerateRadius())
      if(Inflameable(Var(0))) 
	    Incinerate(Var(0));
  RemoveObject();
  return(1);

GetIncinerateRadius:
  return(30);
  
Inflameable:
  if(GetCategory(Par(0)) & C4D_Object()||GetCategory(Par(0)) & C4D_Living()||GetCategory(Par(0)) & C4D_Vehicle())
    if(!SEqual(GetProcedure(Par(0)),"ATTACH"))
      if(GetID(Par(0))!=_HGG)
        if(GetMass(Par(0))>1)
		  if(GetHostile(Par(0), Contained()))
		    if(!ObjectCall(Par(0),"HotLaserIncineration"))
              return(1);
  return(0);