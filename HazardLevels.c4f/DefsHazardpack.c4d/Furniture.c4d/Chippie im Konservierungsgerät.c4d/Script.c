Damage:
  SetLocal(0,2,CreateObject(DCHP));
  CastObjects(SHRD,40,20,0,0);
  ChangeDef(_KGL);
  Sound("Discharge");
  Sound("GlassBreak");
  return(1);