#strict

Completion:
  SetAction("Stand");
  return(1);
Damage:
  if(SEqual(GetAction(),"Stand")) if(LessThan(20,GetDamage())) SetAction("Putt");
  if(SEqual(GetAction(),"Stand2")) if(LessThan(20,GetDamage())) SetAction("Putt2");
  return(1);

StandUbereinander:
  ObjectCall(SetVar(0,FindObject(AT3V,-4,-0,8,19)),"TellingMe",this());
  SetAction("Stand2");
  SetPosition(GetX(Var(0)),Sub(GetY(Var(0)),17));
  return(1);

TellingMe:
  SetLocal(0,Par(0));
  return(1);

NewPosition:
  if(Local(0)) SetPosition(GetX(),Sum(GetY(),-12),Local(0));
  if(GetDir()) if(Local(0)) SetPosition(GetX(),Sum(GetY(),-14),Local(0));
  return(1);