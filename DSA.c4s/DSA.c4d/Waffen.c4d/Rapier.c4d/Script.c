#strict

Hit:
  Sound("SwordHit*");
  return(1);

// Basis schaden den der Gegner erleidet * "Fight" Attribut / 100000
Power:
  return(2);

// Rate in % f�r Critical Hit (Der Gegner fliegt weg + doppelter Schaden)
CritRate:
  return(2);

// Speed - wie kleiner umso besser (Wie lange warten, bis n�chste Schlag kommen kann)
Speed:
  return(2);