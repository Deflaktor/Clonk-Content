/*-- Neues Objekt --*/

#strict
#include _YBA

func Initialize() {
  SetCon(100);
  return(SetAction("Stand"));
}

func Hit() {
  SetXDir(0);
}