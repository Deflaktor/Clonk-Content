
CheckLost:
  if (Or( ActIdle(), Not(GetAlive(GetActionTarget())) )) ChangeDef(SH3A);
  //if(SEqual(GetAction(GetActionTarget()),"Dead")) ChangeDef(SH3A);
  return(1);
  
//Schild wird abgelegt
Unbuckle:
  ChangeDef(SH3A);
  Sound("Connect");
  return(1);  