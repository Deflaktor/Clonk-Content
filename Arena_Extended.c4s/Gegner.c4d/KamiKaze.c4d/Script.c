/* Mini KI */

#strict
#include KIL1

ExplodeKamikaze:
  if(died == 2) {
    CreateObject(PRNT,0,3,killedBy)->Explode(30);
	CreateObject(PRNT,0,3,killedBy)->Explode(30);
  } else {
    Explode(30,CreateObject(PRNT,0,3));
    Explode(30,CreateObject(PRNT,0,3));
  }
  return(1);

ExplodeDistance:
  return(16);  
  
Initialize:
  _inherited();
  weap=KAZE;
  return(0);