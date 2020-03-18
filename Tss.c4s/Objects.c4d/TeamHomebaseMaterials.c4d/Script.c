/*-- Gemeinschaftskonto --*/

#strict

/* Initialisierung */

protected func Initialize()
{
  // Spieler ohne Konto?
  for(var i = 0; i < GetPlayerCount(); ++ i)
  {
    CreateObject(_CNT,0, 0, GetPlayerByIndex(i) );
  }
}

public func InitializePlayer(iPlr)
{
  // Neuer Spieler, neues Konto
  var old; if (old=FindObjectOwner(_CNT, iPlr)) RemoveObject(old);
  CreateObject(_CNT, 0,0, iPlr);
}

protected func Activate(caller) {
  MessageWindow(GetDesc(), caller);
  return(1);
}


protected func Destruction()
{
  // Keine Teamaccounts, keine Konten
  // fixme: Sollte Gemeinschaftskonten vorher auflösen...
  if (ObjectCount(GetID())<=1) RemoveAll(_CNT);
  return(1);
}
