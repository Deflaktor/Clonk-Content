
Process:
  if (GreaterThan(GetActTime(),10)) return(AssignRemoval());
  return(1);

Completion:
  SetAction("Sparkle");
  return(1);
