#strict

Initialize:
SetLocal(6,60);
return(1);

/* Feuern */
Fire:
  // Noch beim Nachladen oder beim Schiesen
  if (SEqual(GetAction(),"Reload")) return(0);
  if (SEqual(GetAction(),"Laden")) return(0);
  // Ammo aufladen
  SetAction("Laden");
  if(Local(5)<1)
  SetLocal(5);
  return(1);

Effekt:
  // Effekt
  SetVar(1,GetDir(Contained()));
  while(LessThan(Var(),361)) And(SetR(Var(),CreateObject(PUL2,Var(1)*5,2,GetOwner(this()))),SetVar(0,Sum(Var(),15)));
  Sound("LaserSchussA");
  return(1);

Feuer:   // FEUER!
  SetVar(0,CreateContents(GetAmmoID()));
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Contained()),Var(0)); 
  // Richtung des Trägers abfragen
  SetVar(1,GetDir(Contained()));
  // Ammo abfeuern
  Exit(Var(0), Sum(-12,Mul(Var(1),24)),0,0, 0,0,0 );
  ObjectCall(Var(0),"Launch",Var(1));
  // Sound
  Sound("Purge1");

/*var i;
for(i=0;i<50;i++) {
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Contained()),Var(0)); 
  // Richtung des Trägers abfragen
  SetVar(1,GetDir(Contained()));
  if(Var(1))
  Exit(SetVar(0,CreateContents(GetAmmoID())), Sum(12,i),0,0, 0,0,0 );
  if(!Var(1))
  Exit(SetVar(0,CreateContents(GetAmmoID())), Sub(-12,i),0,0, 0,0,0 );
  ObjectCall(Var(0),"Launch",Var(1)); }*/


  if(Local(5)>60)
  SetLocal(5,Local(6));
  return(1);

Reloaden:
SetLocal(5,Local(5)-1);
if(FindContents(GetID(),Contained())==this())
MunUpdate(Contained());
return(Local(5));

Reloaden2:
SetLocal(5,Local(5)+1);
if(FindContents(GetID(),Contained())==this())
MunUpdate(Contained());
return(Local(5));

MunUpdate:
if(Not(FindContents(GetID(),Contained())==this()))
return(0);
  SetPhysical("Magic",0,2,Par(0));
  DoMagicEnergy(0,Par(0));
  SetPhysical("Magic",100000,2,Par(0));
if(Local(5)<1)
  DoMagicEnergy(100,Par(0));
if(Local(5)>0)
  DoMagicEnergy(Sum(Mul(Div(Mul(Local(5),100),Local(6)),-1),100),Par(0));
  return(1);

Collection:
MunUpdate(Contained());
return(1);

/* Objekt Munition */
public MaxAmmo:
  return(-1);
  
Selection:
  MunUpdate(Contained());
  Sound("Combo6");
  return(1);


/* Objekt ist eine Waffe */
IsWeapon:
  return(LongRangeWeapon());
  
/* Objekt wurde ausgewählt */
Selection:
  Sound("Launch2");
  return(1);
  
/* Ammo IDs */  
GetAmmoID:
  return(_SSS);
GetAmmoPacketID:
  return(0);