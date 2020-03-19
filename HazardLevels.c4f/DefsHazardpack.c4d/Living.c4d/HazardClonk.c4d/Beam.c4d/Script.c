#strict

protected Initialize:
  SetPosition(GetX(),GetY()+18);
  return(SetAction("Sparkle2"));

Removal:
  return(RemoveObject());