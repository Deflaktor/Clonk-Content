Initialize:
  SetAction("Los");
  return(1);

Test:
  if(SetLocal(1,FindObject(0,-50,-50,100,100,OCF_CrewMember()))) Erstellen();
  return(1);

Erstellen:
  SetLocal(0,2,CreateObject(_CHP));
  CastObjects(SHRD,40,20,0,0);
  ChangeDef(_KGL);
  Sound("Discharge");
  Sound("GlassBreak");
  return(1);

Damage:
  SetLocal(0,2,CreateObject(_CHP));
  CastObjects(SHRD,40,20,0,0);
  ChangeDef(_KGL);
  Sound("Discharge");
  Sound("GlassBreak");
  return(1);