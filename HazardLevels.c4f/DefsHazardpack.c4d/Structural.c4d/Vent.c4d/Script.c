#strict

Check:
if(!(CheckEnergy()))
{
if(GetAction()S="Vent")
return(SetAction("Stop"));
if(GetAction()S="Start")
return(SetAction("Stop2"));
if(GetAction()S="Start2")
return(SetAction("Stop"));
SetLocal(0,1);
}
return(0);

Check2:
if(CheckEnergy())
{
if(GetAction()S="Idle")
return(SetAction("Start"));
if(GetAction()S="Stop")
return(SetAction("Start2"));
if(GetAction()S="Stop2")
return(SetAction("Start"));
}
return(1);

Completion:
  SetAction("Vent");
  return(1);

CheckEnergy:
  if (Not(GameCall("MainEnergySupply", this()))) return(0);
return(1);
