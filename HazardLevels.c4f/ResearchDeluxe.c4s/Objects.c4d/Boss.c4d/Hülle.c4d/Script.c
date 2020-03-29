#strict

Initialize:
  SetAction("Normal");
  SetSolidMask(134,0,134,234);
  return(1);

Damage:
  if(GetAction()S="Kaputt") return(1);
  if(GetDamage()>300) return(Kaputt());
  if(GetDamage()>200) return(SetAction("Schaden2"));
  if(GetDamage()>100) return(SetAction("Schaden1"));
  return(1);

Kaputt:
  SetAction("Kaputt");
  SetSolidMask(269,0,134,234);
  // Crack open
  CastObjects(SHRP,5,20,0,-100);
  CastObjects(_TF2,5,20,0,-100);
  Sound("Blast2");
  CreateObject(KG5B,21,-100+21);
  return(1);