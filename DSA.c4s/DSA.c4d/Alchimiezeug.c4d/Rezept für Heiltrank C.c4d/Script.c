Hit:
  Sound("Paper1.wav");
  return(1);

Activate:
  SetVar(0,FindContents(AC3A, Contained()));
  if(Not(Var(0))) Message("Ohne Alchimieset läuft gar nichts!",this());
  if(Var(0))  if(Sound("Paper*"))  Enter(Var(0),this());
  return(1);

Fertig:
  CreateContents(P33A);
  Exit(Contents());
  RemoveObject();
  return(1);

Selection:
  Sound("Paper2.wav");
  return(1);