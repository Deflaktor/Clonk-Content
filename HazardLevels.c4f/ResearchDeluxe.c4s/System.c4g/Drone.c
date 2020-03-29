#strict
#appendto _DRN

DestroyIt:
  RemoveObject();
  ObjectCall(CreateObject(EXPL),"Launch",30);
  CastObjects(_DFR,3,40,0,0);
  CastObjects(_DFS,6,40,0,0);
  return(1);
