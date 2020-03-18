Initialize:
  RemoveObject();
  SetAction("BinDa");
  return(1);

Hit:
  RemoveObject();
  return(1);

Glitzer:
  if(GreaterThan(GetActTime(),40)) Hit();
  CreateObject(_PCG);
  return(1);