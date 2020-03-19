#strict

Wind2Float:
  SetXDir( BoundBy(GetWind()/4,-20,20)+Random(41)-20 );
  return(1);

Activate:
  SetAction("Smoke");
  SetPhase(Random(4));
  SetComDir(COMD_Up());
  Wind2Float();
  return(1);

Remove:
  RemoveObject();
  return(1);
