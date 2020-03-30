/*-- Bergarbeiter --*/

#strict

#include CLNK
/*
Incineration:
  SetXDir(-10);
  SetYDir(-50);
  Extinguish();
  return(1);
*/
Death:
  ObjectCall(FindObject(_S10),"Initialize");
  RemoveObject();
  return(1);

RejectCollect:
  return(1);
