#strict

Launch:
  DoCon(100);
  SetLocal(0,Par(0));
  SetOwner(GetOwner(Par(0)));
  SetAction("Start");
  SetLocal(1,170);
  return(1);
Kill:
  SetLocal(1,Local(1)-1);
  if(Local(1)<1)
    return(Remove());
  return(1);
Remove:
  // Alle Warnleuchten aktivieren
  while (SetVar(0, FindObject(WALE,0,0,0,0,0, 0,0, NoContainer(), Var(0)) ))
      ObjectCall( Var(0) ,"On");
  // Global aktivieren damit nicht mehr Respawned wird
  SetGlobal(340,1);
  // Boss löschen
  if(Local(0))
    RemoveObject(Local(0));
  Explode(30, FindObject(_DRB));
  // Nuklear Explosion aktivieren und CountDown
  ObjectSetAction(CreateObject(NEBE,0,0,-1),"Activated");
  ObjectCall(CreateObject(EXPL),"Launch",150);
  CreateObject(SDS1,0,0,-1);
  return(RemoveObject());
