/*-- Zerstörter Panzer --*/

Initialize:
RemoveObject();
SetAction("Destroyed");
Incinerate();
return(1);

private Effects:
  if (Not(OnFire())) return(1);
  Smoke(Sum(-20,Random(40)),Sum(-20,Random(10)),Sum(10,Random(20)));
  if (GreaterThan(GetActTime(),500)) And(CastObjects(_DF1,15,50,0,-20),Explode(30));
  return(1);