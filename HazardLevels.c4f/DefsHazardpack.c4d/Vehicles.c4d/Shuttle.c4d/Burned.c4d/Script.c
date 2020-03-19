/*-- Zerstörtes Shuttle --*/

private Effects:
  if (OnFire())
  Smoke(Sum(-50,Random(100)),Sum(-20,Random(40)),Sum(10,Random(20)));
  return(1);

Damage:
  if(GetDamage()>1000)
    Boom();
  return(1);

Boom:
  CastObjects(_DFR,6,100,0,0);
  CastObjects(_DFS,5,100,0,0);
  CastObjects(_DFR,6,110,0,0);
  CastObjects(_DFS,5,110,0,0);
  CastObjects(_DFR,6,120,0,0);
  CastObjects(_DFS,5,120,0,0);
  CastObjects(_DFR,6,130,0,0);
  CastObjects(_DFS,5,130,0,0);
  CastObjects(_DFR,6,140,0,0);
  CastObjects(_DFS,5,140,0,0);
  CastObjects(_DFR,6,150,0,0);
  CastObjects(_DFS,5,150,0,0);
  RemoveObject();
  ObjectCall(CreateObject(EXPL),"Launch",80);
  return(1);