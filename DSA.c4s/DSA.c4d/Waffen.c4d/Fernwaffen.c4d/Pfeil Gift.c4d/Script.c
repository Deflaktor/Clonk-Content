Hit:
  if(SEqual(GetAction(),"Shot"))  Call("ichwerdniemehrfliegen");
  SetAction("Idle");
  SetVar(0,CreateObject(GI3A));
  ObjectCall(Var(0),"Gift",15,1);
  SetLocal(0,Local(0),Var(0));
  SetLocal(2,1);
  RemoveObject();
  return(1);

ichwerdniemehrfliegen:
  if(Equal(Random(2),0))  Call("AdeDuSchnoedeWelt");
  SetAction("Idle");
  return(1);

AdeDuSchnoedeWelt:
  ChangeDef(PK3A,this());
  SetAction("DieHard");
  return(1);

InFlight:
  if(SetLocal(0,FindObject(0,-8,-8,16,16,OCF_Living(),0,0,NoContainer())))     if(Not(Equal(Local(0),Local(1))))  Call("Damage");
  if(Local(2)==2) CreateObject(_TRS);
  return(1);

Damage:
  Punch(Local(0),3*Local(2));
  SetVar(0,CreateObject(GI3A));

//Par(0) ist Anzahl Sekunden und Par(1) ist Schaden je Sekunde. Local(0) ist das Ziel
  ObjectCall(Var(0),"Gift",15,1);
  SetLocal(0,Local(0),Var(0));
  RemoveObject();
  return(1);

//Local(1) ist der schiessende Held
Start:
  SetLocal(1,Par(0));
  SetAction("Launch");
  return(1);