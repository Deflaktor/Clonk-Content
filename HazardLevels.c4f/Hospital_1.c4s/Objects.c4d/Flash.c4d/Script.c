/*-- Sirene --*/

Initialize:
  SetAction("Flash");
  return(1);

Damage:
  if (SEqual(GetAction(),"Broken")) return(0);
  SetAction("Broken");
  CastObjects(SHRD,8,28,0,-5);
  Sound("GlassBreak");
  return(1);
