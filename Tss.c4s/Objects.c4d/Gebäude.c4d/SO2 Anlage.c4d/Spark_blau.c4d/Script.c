Initialize:
  SetAction("BinDa");
  return(1);

Hit:
  RemoveObject();
  return(1);

Glitzer:
  if(GreaterThan(GetActTime(),35)) Hit();
  CreateObject(_PRC);
  return(1);