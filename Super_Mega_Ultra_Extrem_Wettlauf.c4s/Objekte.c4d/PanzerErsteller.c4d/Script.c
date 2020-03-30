Initialize:
  SetAction("Los");
  return(1);

Test:
  while(SetLocal(0,FindObject(CLNK,-25,-80,50,160,OCF_CrewMember(),0,0,NoContainer()))) return(ObjectCall(this(),"Erstellen"));
  return(1);

Erstellen:

  SetVar(1,CreateObject(PM7K,0,-5,GetOwner(Local())));
  SetOwner(GetOwner(Local()),Var(1));
  Enter(Var(1),Local(0));

  return(1);