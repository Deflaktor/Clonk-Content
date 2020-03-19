/*-- HazardClonk mit Gravity-Suit --*/

#strict
#include HCK2


/* Initialisierung */  
Init:
  //SetPhysical( "Energy", GetPhysical("Energy",1)*150/100, 2 );
  SetPhysical( "Energy", GetPhysical("Energy",1)+50*1000, 2 );
  DoEnergy(50);
  SetPhysical( "Swim", GetPhysical("Swim",1)/100*130, 2 );
  SetPhysical( "Breath", GetPhysical("Breath",1)*2, 2 );
  SetAction("Walk");
  return(1);
