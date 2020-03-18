#strict
#include PRNT

/*-- Neues Objekt --*/

Initialize:
  if(FindObject(SRKR)) {
    ChangeDef(GameCall("Zufallsflint2"));
    return(ObjectCall(this(),"Initialize"));
  }
  return(1);

Hit:
  BlowUp();
  return(1);

Entrance:
  SetOwner(GetOwner(Par(0)),this());
  return(1);

BlowUp:
  SetOwner(GetOwner(),CreateObject(_SLC,0,0));
  return(RemoveObject());  
