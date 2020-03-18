/*-- Monsterjagd --*/

#strict
#include GOAL

public func IsFulfilledforPlr (plr) {

  // Objekt ist gebaut
  if(FindObjectOwner(GLZ8, plr, 0, 0, 0, 0, OCF_Fullcon())) 
    return(1);

  return (0);
}

public func IsFulfilled()
{
  if (Local(2))
    return(1);
  SetLocal(1,0);
  var j;
  var fulfilled = false;
  for (var i = GetPlayerCount (); i; ++j)
    if (GetPlayerName(j)) {
      --i;
      if (!IsFulfilledforPlr (j)) SetLocal(1,Local(1)+1);
	    else fulfilled = true;
    }
  if(fulfilled) return(1); // Diese Zeile kommentieren damit alle Spieler einen Mondglaspalast bauen müssen.
  if (Local(1)||!GetPlayerCount())
    return(0);
  SetLocal(2,1);
  return(1);
}

protected func Activate(iPlayer)
{
  if (Local(2))
    return(MessageWindow("$MsgMoonglaspalaceBuilt$", iPlayer));
  if (Local(1))
    if (FindObject(GLZ8, 0, 0, 0, 0, OCF_Fullcon()))
      return(MessageWindow(Format("$MsgMoonglaspalaceBuiltNAP$", Local(1)), iPlayer));
  return(MessageWindow("$MsgMoonglaspalaceNotBuilt$", iPlayer));
}