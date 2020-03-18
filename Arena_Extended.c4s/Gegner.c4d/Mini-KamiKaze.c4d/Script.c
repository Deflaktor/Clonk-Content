/* Mini KI */

#strict
#include KIL1
ExplodeKamikaze:
  if(died == 2) {
    CreateObject(PRNT,0,3,killedBy)->Explode(8);
  } else {
    Explode(8,CreateObject(PRNT,0,3));
  }
  return(1);
 
ExplodeDistance:
  return(16);

Initialize:
  _inherited();
  DoCon(-50);
  weap=KAZE;
  return(0);