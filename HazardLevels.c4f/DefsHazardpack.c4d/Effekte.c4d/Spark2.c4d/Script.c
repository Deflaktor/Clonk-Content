#strict

Process:
  SetClrModulation(RGBa(255,255,255,GetActTime()*255/20));
  if (GreaterThan(GetActTime(),20)) return(AssignRemoval());
  return(1);

Initialize:
  SetAction("Sparkle");
  return(1);
