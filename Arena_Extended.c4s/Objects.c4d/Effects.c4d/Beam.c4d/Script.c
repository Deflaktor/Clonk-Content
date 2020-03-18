protected Initialize: return(SetAction("Sparkle"));

Init:
SetLocal(0,Par(0));
return(1);

protected CastFlint:
  if(Local(0))
    SetR(Random(360),CreateObject(Local(0)));
  return(1);

Removal:
  return(RemoveObject());