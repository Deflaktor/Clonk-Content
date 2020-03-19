#strict

Check:
if(!(CheckEnergy()))
if(GetAction()S="Scroll")
SetAction("Aus");
if(CheckEnergy())
if(GetAction()S="Aus")
SetAction("Scroll");
return(1);

Completion:
  SetAction("Scroll");
  return(1);

Damage:
  if (SEqual(GetAction(),"Broken")) return(0);
  SetAction("Broken");
  CastObjects(SHRD,20,10,0,0);
  Sound("GlassBreak");
  return(1);

CheckEnergy:
if (Not(GameCall("MainEnergySupply", this()))) return(0);
return(1);