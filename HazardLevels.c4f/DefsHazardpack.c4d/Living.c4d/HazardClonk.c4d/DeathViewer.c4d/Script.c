#strict

static playerRespawnID;

Init:
  SetAlive(0);
  SetOwner(Par(0));
  SetCrewEnabled(0);
  SetAction("Active");
  return(1);

Remove:
  ChangeDef(GetRespawnID());
  // Wiederbeleben
  ObjectCall(this(),"Respawn");
  ObjectCall(this(),"Init");
  SetCursor(GetOwner(),this());
  // Punktverlust
  DoScore(GetOwner(),-250);
  // Meldung
  Log("Neuer Einsatz: %s",GetPlayerName(GetOwner()));
  // Heilen
  SetAlive(1);
  DoEnergy(100);
  // Löschen
  Extinguish();
  // Rauswerfen
  GameCall("DeployPlayer",GetOwner());
  return(1);

GetRespawnID:
  if(!playerRespawnID)
    return(HZCK);
  return(playerRespawnID);