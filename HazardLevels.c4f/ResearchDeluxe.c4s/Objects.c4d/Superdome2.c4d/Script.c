#strict

Initialize:
  SetAction("Exist");
  SetSolidMask(124,0,122,44,0,0);
  return(1);

Damage:
  if(GetAction() S= "Destroyed")
    return(1);
  if(GetDamage()>250) {
    Sound("Discharge");
    Sound("GlassBreak");
    SetAction("Destroyed");
    CastObjects(_TF1,1,30,-40);
    CastObjects(_TF2,3,40,-40);
    CastObjects(_TF1,1,30,40);
    CastObjects(_TF2,3,40,40);
    CastObjects(SHRD,40,20);
    SetSolidMask(124,220,122,44,0,0);
  } else if(GetDamage()>200) {
    if(!(GetAction() S= "Damaged4")) {
      CastObjects(SHRD,4,20);
      Sound("Discharge");
      SetAction("Damaged4");
    }
  } else if(GetDamage()>150) {
    if(!(GetAction() S= "Damaged3")) {
      CastObjects(SHRD,4,20);
      Sound("Discharge");
      SetAction("Damaged3");
    }
  } else if(GetDamage()>100) {
    if(!(GetAction() S= "Damaged2")) {
      CastObjects(SHRD,4,20);
      Sound("Discharge");
      SetAction("Damaged2");
    }
  } else if(GetDamage()>50) {
    if(!(GetAction() S= "Damaged1")) {
      CastObjects(SHRD,4,20);
      Sound("Discharge");
      SetAction("Damaged1");
    }
  }
  return(1);

Pump:
  if(GetAction() S= "Destroyed")
    return(1);
  // Wasser absaugen
  for(var i=0;i<300;++i) {
    if(ExtractLiquid(0,18)==-1) {
      return(1);
    }
  }
  return(1);
