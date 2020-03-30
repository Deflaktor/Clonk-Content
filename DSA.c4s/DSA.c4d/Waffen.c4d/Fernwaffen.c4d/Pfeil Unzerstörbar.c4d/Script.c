//Local(1) ist der schiessende Held

Start:
  SetLocal(1,Par(0));
  SetAction("Launch");
  return(1);

InFlight:
  if(SetLocal(0,FindObject(0,-30,-30,60,60,OCF_Alive(),0,0,NoContainer())))
    if(Not(Equal(Local(0),Local(1))))  Call("Damage");    
  if(Local(2)==2) CreateObject(_TRS);
  return(1);

Hit: 
  SetLocal(2,1);
  SetAction("Idle");
  return(1);

Damage:
  Punch(Local(0),15*Local(2));
  SetAction("Idle");
  Enter(Local(0));
  return(1);