Hit:
  Sound("RockHit");
  return(1);

Activate:
  Sound("RadioStatic");
  CreateMenu(SHT1,Par(0),this());
  AddMenuItem("%s","MenuPickup",MI_P,Par(0));
  //AddMenuItem("%s","MenuReinforcements",MI_R,Par(0));
  return(1);

MenuPickup:
  if (SetVar(0,GameCall("FindPlayerShuttle",GetOwner())))
    ObjectCall(Var(0),"PickupCall",GetX(),GetY());
  return(1);

/*MenuReinforcements:
  if (Not(GameCall("OrderReinforcements",GetOwner())))
    Message("Noch nicht freigegeben",this());
  return(1);*/

SelfDestruct:
  SetAction("SelfDestruct");
  return(1);

Destruct:
  RemoveObject();
  return(1);