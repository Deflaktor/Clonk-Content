// Local(0) - Energiebalken

Initialize:
  SetAction("On");
  SetLocal(0,CreateObject(_BAR,7,3));
  return(1);

Damage:
  if (SEqual(GetAction(),"Broken")) return(0);
  SetAction("Broken");
  CastObjects(SHRD,20,35,0,0);
  Sound("GlassBreak");
  RemoveObject(Local(0));
  return(1);

CheckEnergy:
  if(Equal(GameCall("GetGlobalEnergy"),0))
    return(SetAction("Off"));
  SetAction("On");
  if(Not(Local(0)))
    SetLocal(0,CreateObject(_BAR,7,3));
  return(1);