/*-- Neues Objekt --*/

#strict

IsAmmo:
  return(1);
  
Timer:
  if(GBackSolid(0,0)) if(GBackLiquid(0,-2)) SetPosition(GetX(),GetY()-1);
  return(1);