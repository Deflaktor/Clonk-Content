/*-- Dronentür --*/

#strict

CheckArea:
  // Drone im Bereich suchen
  SetVar(0,FindObject(_DRN,-16,-15,32,30,));
  // Drone da, öffnen
  if (Var(0)) 
    Open();
  // Wenn keine Drone da, schließen
  if (Not(Var(0))) 
    Close();
 return(1);

Open:
  if(Not(ActIdle())) return(1);
  SetAction("OpenDoor");
  return(1);

Close:
  if(Not(SEqual(GetAction(),"DoorOpen"))) return(1);
  SetAction("CloseDoor");
  return(1);

Initialize:
  PutSolidMask();
  return(1);
     
RemoveSolidMask:
  SetSolidMask();
  return(1);

PutSolidMask:
  SetSolidMask(0,1,32,2,0,1);
  return(1);
        
SoundOpen:
  Sound("Airlock1");
  return(1);
SoundClose:
  Sound("Airlock2");
  return(1);
 
Damage:
  if ( LessThan( GetDamage(), 70 ) ) return(0);
  CastObjects(_DF2,3,50,0,-5);
  CastObjects(SHRP,10,30,0,0);
  RemoveObject();  
  Sound("Discharge");
  Sound("Blast2");
  return(1);
  