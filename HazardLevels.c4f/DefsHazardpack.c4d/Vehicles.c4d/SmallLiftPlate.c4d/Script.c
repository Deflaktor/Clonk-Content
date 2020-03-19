#strict
#include _LFP
/*-- Kleine Schwebeplatte --*/

/* Lokale Variablen */

// 0: Horizontale an/aus
// 1: Vertikale an/aus
// 2: ComDir für ResumeTravel, X/Y für SpeedTo
// 3: Y Obergrenze gesetzt
// 4: Y Obergrenze Transfer
// 5: Y Untergrenze Transfer

/* Steuerung */

DigFree:
  DigFreeRect(GetX()-Width()/2, GetY()+4, Width(), 9);
  return(1);

Width:
  return(31);
  
/* Status */
public Passenger:
  return( FindObject(0, -Width()/2,-11,Width(),16, OCF_CrewMember(),0,0,NoContainer()) );

  