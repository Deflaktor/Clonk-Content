/*-- Zerstörter Panzer --*/

private Effects:
  if (Not(OnFire())) return(1);
  Smoke(Sum(-20,Random(40)),Sum(-20,Random(10)),Sum(10,Random(20)));
  return(1);