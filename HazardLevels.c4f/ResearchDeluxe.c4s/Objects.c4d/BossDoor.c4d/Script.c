/*-- Dronentür --*/

#strict
#include _DR0

CheckArea:
  if(!GetEnergy()) {
    if(GetAction() eq "DoorActive")
      SetAction("Idle");
    return(Close());
  }
  if(GetAction() eq "Idle")
    SetAction("DoorActive");
  // Drone im Bereich suchen
  SetVar(0,FindObject(0, -20,-16,31,32, OCF_CrewMember()));
  // Drone da, öffnen
  if (Var(0)) 
    if( Equal( GetComDir( Var(0) ),COMD_Stop() ) || GetAction(Var(0)) eq "Swim" ) 
      Open();
  // Wenn keine Drone da, schließen
  if (Not(Var(0))) 
    Close();
 return(1);

RemoveSolidMask:
  SetSolidMask(120,0,20,32,0,0);
  return(1);
 
PutSolidMask:
  SetSolidMask(0,0,20,32,0,0);
  return(1);
  
Damage:
  return(1);
