BruceWillis:
  SetLocal(5,Sum(Local(5),+1));
  if(GreaterThan(Local(5),1)) RemoveObject();
  return(1);