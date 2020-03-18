/* Mini KI */

#strict
#include KIL1

WeapID: 
  if(weap!=P57M) { 
    ChangeDef(KIL1);
	this()->Initialize();
	this()->SetWeapID(weap);
  }
  if(weap) return(weap);
  return(FLNT);
  
SetRandomColor:
  SetColor(0);
  return(1);