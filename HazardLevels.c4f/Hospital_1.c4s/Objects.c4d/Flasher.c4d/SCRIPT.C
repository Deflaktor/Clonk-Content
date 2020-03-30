
/* Feuern */
public Fire:
  // Noch beim Nachladen
  if (SEqual(GetAction(),"Reload")) return(0);
  // Träger
  SetVar(0,Contained());
  // Richtung des Trägers abfragen
  SetVar(1,GetDir(Contained()));
  // Ammo abfeuern
  if(Equal(Var(1),0))
    LaunchLightning(GetX(Var(0)),GetY(Var(0)),-10,0,-1,3);
  if(Equal(Var(1),1))
    LaunchLightning(GetX(Var(0)),GetY(Var(0)),10,0,-1,3);
  // Sound
  Sound("LaserShot1");
  // Nachladen
  SetAction("Reload");
  return(1);

/* Objekt ist eine Waffe */
public IsWeapon:
  return(1);
  
/* Objekt wurde ausgewählt */
public Selection:
  Sound("Purge2");
  return(1);
  
/* Ammo IDs */  
private GetAmmoID:
  return(0);
private GetAmmoPacketID:
  return(0);