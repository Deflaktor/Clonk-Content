/*-- Neues Objekt --*/

#strict

Check:
if(GetAction()S="kaputt")
return(1);
if(CheckEnergy())
if(Local(0))
  SetAction("leucht");
if(!(CheckEnergy()))
  SetAction("Idle");
if(!(Local()))
  SetAction("Idle");
  return(1);

On:
SetLocal(0,1);
return(1);

Off:
SetLocal();
return(1);

CheckEnergy:
if (Not(GameCall("MainEnergySupply", this()))) return(0);
return(1);

Damage:
  if (SEqual(GetAction(),"kaputt")) return(0);
  CastObjects(SHR2,5,20,0,0);  
  Sound("Discharge");
  Sound("GlassBreak");
  SetAction("kaputt");
  return(1);
