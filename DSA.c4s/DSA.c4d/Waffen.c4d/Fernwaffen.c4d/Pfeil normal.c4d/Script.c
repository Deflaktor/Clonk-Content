Hit:
  if(SEqual(GetAction(),"Shot"))  Call("ichwerdniemehrfliegen");
  SetAction("Idle");
  ChangeDef(PK3A);
  return(1);

ichwerdniemehrfliegen:
  if(Equal(Random(3),0))  Call("AdeDuSchnoedeWelt");
  return(1);

AdeDuSchnoedeWelt:
  ChangeDef(PK3A);
  SetAction("DieHard");
  return(1);

InFlight:
  if(SetLocal(0,FindObject(0,-8,-8,16,16,OCF_Living(),0,0,NoContainer())))     if(Not(Equal(Local(0),Local(1))))   Call("Damage");
  if(Local(2)==2) CreateObject(_TRS);
  return(1);

Damage:
  Punch(Local(0),10*Local(2));
  SetAction("Idle");
  Enter(Local(0));
  Call("ichwerdniemehrfliegen");
  ChangeDef(PK3A);
  return(1);

//Local(1) ist der schiessende Held

Start:
  SetLocal(1,Par(0));
  SetAction("Launch");
  return(1);