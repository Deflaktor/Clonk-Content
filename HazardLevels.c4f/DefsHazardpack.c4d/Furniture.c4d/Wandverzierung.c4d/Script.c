#strict


Damage:
  if(GetComponent(PUTT)) return(0);
  SetComponent(PUTT,1);
  if(SEqual(GetAction(),"Stand3")) return(SetAction("Stand3Damage"));
  if(SEqual(GetAction(),"Stand4")) return(SetAction("Stand4Damage"));
  RemoveObject();
  return(1);