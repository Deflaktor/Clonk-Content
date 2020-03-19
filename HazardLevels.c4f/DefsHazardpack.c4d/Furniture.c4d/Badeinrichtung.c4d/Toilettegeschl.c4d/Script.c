#strict

ControlUp:
  if(GetComponent(PUTT)) return(0);
  if(SEqual(GetAction(),"Idle")) return(SetAction("OpenDoor"));
  if(SEqual(GetAction(),"DoorOpen")) return(0);
  if(Equal(GetPhase(),0)) SetVar(0,4);
  if(Equal(GetPhase(),1)) SetVar(0,3);
  if(Equal(GetPhase(),2)) SetVar(0,2);
  if(Equal(GetPhase(),3)) SetVar(0,1);
  if(Equal(GetPhase(),4)) SetVar(0,0);
  SetAction("OpenDoor");
  SetPhase(Var(0));
 return(1);

ControlDownSingle:
  if(GetComponent(PUTT)) return(0);
  if(SEqual(GetAction(),"DoorOpen")) return(SetAction("CloseDoor"));
  if(SEqual(GetAction(),"Idle")) return(0);
  if(Equal(GetPhase(),0)) SetVar(0,4);
  if(Equal(GetPhase(),1)) SetVar(0,3);
  if(Equal(GetPhase(),2)) SetVar(0,2);
  if(Equal(GetPhase(),3)) SetVar(0,1);
  if(Equal(GetPhase(),4)) SetVar(0,0);
  SetAction("CloseDoor");
  SetPhase(Var(0));
 return(1);

Damage:
  if(LessThan(20,GetDamage())) if(Not(GetComponent(PUTT))) SetAction(Format("Damage%d",Sum(1,Random(2))))&&SetComponent(PUTT,1);
  return(1);