#strict

Damage:
  if(Not(GetComponent(PUTT))) SetAction(Format("%sDamage",GetAction()));
  if(SEqual(GetAction(),"Idle"))  SetAction("Stand0Damage");
  SetComponent(PUTT,1);
  return();