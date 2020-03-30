/*-- Axt --*/

Hit:
  Sound("MetalHit*");
  return(1);

// Basis schaden den der Gegner erleidet * "Fight" Attribut / 100000
Power:
  return(6);

// Rate in % für Critical Hit (Der Gegner fliegt weg + doppelter Schaden)
CritRate:
  return(100);

// Speed - wie kleiner umso besser (Wie lange warten, bis nächste Schlag kommen kann)
Speed:
  return(15);

