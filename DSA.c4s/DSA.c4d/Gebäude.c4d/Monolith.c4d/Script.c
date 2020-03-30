Initialize:
  SetAction("Wait");
  SetVar(0,CreateObject(MS3A,0,20));
  SetLocal(1,Var(0));
  SetLocal(0,this(),Var(0));
  return(1);

ControlUp:
  SetLocal(0,Par(0));
  if(SEqual(GetAction(),"Wait")) Call("SicherheitsAbfrage");
  return(1);

SicherheitsAbfrage:
  SetAction("burk");
  Message("Wollen Sie sich wirklich zum Gate Teleportieren?",this());
  CreateMenu(0,Local(0),this());
  AddMenuItem("Ja","Etwas",MM3A,Local(0));
  AddMenuItem("Nein","Nichts",MM3A,Local(0));
  return(1);

Etwas:
  SetAction("busy");
  return(1);

Nichts:
  SetAction("Wait");
  return(1);

GateTelep:
  CastObjects(SPAR,10,10);
  SetPosition(GetX(Global(0)),GetY(Global(0)),Local(0));
  return(1);