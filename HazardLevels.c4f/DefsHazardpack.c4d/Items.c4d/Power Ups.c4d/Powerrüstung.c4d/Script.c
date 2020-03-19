#strict

// Befehl vom HazardClonk, um zu aktivieren:
Activate:
  SetLocal(0,Contained());
  if(GetID(Contained())==HZCK) {
    Local(0)->PutArmorOn(HCK3);
    return(RemoveObject());
  } else if(GetID(Contained())==HCK2) {
    Local(0)->PutArmorOn(HCK4);
    return(RemoveObject());
  } else if(GetID(Contained())==HCK3) {
    Message("Die Power-Suit wird bereits getragen.",Contained());
    return(0);
  } else if(GetID(Contained())==HCK4) {
    Message("Die Power-Suit wird bereits getragen.",Contained());
    return(0);
  } else
    Message("Die Power-Suit kann nicht getragen werden.",Contained());
return(0);