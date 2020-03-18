#strict

Initialize:
  SetAction("Checking");
  return(1);

Hit:
  Explode(8);
  return(1);

Checkit:
  if(FindObject(CLON,-5,-5,10,10)) Hit();
  return(1);