//** Geschwindigkeitsoptimierer-Implantat **//
// 0 = Maximale Laufzeit des Implantates
// 1 = Bisherige Laufzeit des Implantates

Initialize:
  return(1);

// Befehl vom HazardClonk, um Implantat zu aktivieren:
Activate:
  // Implantat-Funktion aktivieren:
if(Local(3,Contained())==0) {
  SetLocal(3,1,Contained());
  SetPhysical("Walk",GetPhysical("Walk",0,Contained())+20000,2,Contained());
  SetPhysical("Jump",GetPhysical("Jump",0,Contained())+4000,2,Contained());
  RemoveObject(this());
}
  return(0);