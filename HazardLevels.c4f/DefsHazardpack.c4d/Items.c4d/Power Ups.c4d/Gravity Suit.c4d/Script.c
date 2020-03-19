#strict

// Befehl vom HazardClonk, um Implantat zu aktivieren:
Activate:
  SetLocal(0,Contained());
  if(GetID(Contained())==HZCK) {
    Local(0)->PutArmorOn(HCK2);
    return(RemoveObject());
  } else if(GetID(Contained())==HCK2) {
    Message("Die Gravity-Suit wird bereits getragen.",Contained());
    return(0);
  } else if(GetID(Contained())==HCK3) {
    Local(0)->PutArmorOn(HCK4);
    return(RemoveObject());
  } else if(GetID(Contained())==HCK4) {
    Message("Die Gravity-Suit wird bereits getragen.",Contained());
    return(0);
  } else
    Message("Die Gravity-Suit kann nicht getragen werden.",Contained());
return(0);