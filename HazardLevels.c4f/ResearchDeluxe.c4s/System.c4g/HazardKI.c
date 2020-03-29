/*-- Neues Script --*/

#strict
#appendto HK00
#appendto HK01

// Im story mode sammeln sie nix ein
RejectCollect:
  if(Global(6))
    return(1);
  return(_inherited());