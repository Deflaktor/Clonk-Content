Initialize:
  SetAction("Los");
  return(1);

Test:
  while(SetLocal(0,FindObject(CLNK,-25,-80,30,80,OCF_CrewMember(),0,0,NoContainer()))) return(ObjectCall(this(),"Erstellen"));
  return(1);

Erstellen:

  SetVar(1,CreateObject(BIK1,0,-5));
  SetOwner(GetOwner(Local()),Var(1));
  Enter(Var(1),Local(0));
  ObjectSetAction(Var(1),"Act2");

  return(1);