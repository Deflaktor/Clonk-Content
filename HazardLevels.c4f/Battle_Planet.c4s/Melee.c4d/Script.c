/*-- Melee --*/

#strict
#include GOAL

// Local 1: Anfangszahl Spieler

protected InitializePlayer:
  // Mit allen Spielern verfeinden
  var i,j;
  for (j=GetPlayerCount(); j>1; i++) if (GetPlayerName(i) && i != Par())
    {
    SetHostility(i, Par(), 1, 1);
    SetHostility(Par(), i, 1, 1);
    --j;
    }
  return(1);

public IsFulfilled:
  // Anfangszahl Spieler bestimmen
  if (!Local(1))
    if ((Local(1)=GetPlayerCount())<2)
      {
      Log("Zu wenig Teilnehmer für ein Melee.");
      return(RemoveObject());
      }
  // Spielziel überprüfen
  return(GetPlayerCount()<2);

protected Activate: // int iPlr
  if (IsFulfilled()) return(MessageWindow("Dein Gegner ist tot.",Par()));
  MessageWindow(Format("Noch %d Spieler|zu eliminieren",GetPlayerCount()-1),Par());
  return(1);
