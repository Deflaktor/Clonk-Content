/*-- HazardClonk mit Power-Suit --*/

#strict
#include HZCK

/* Initialisierung */  
Init:
  //SetPhysical( "Energy", GetPhysical("Energy",1)*150/100, 2 );
  SetPhysical( "Energy", GetPhysical("Energy",1)+50*1000, 2 );
  DoEnergy(50);
  SetAction("Walk");
  return(1);
