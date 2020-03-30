Initialize:
  SetAction("Los");
  return(1);

Test:
  while(SetLocal(0,FindObject(CLNK,-25,-80,50,160,OCF_CrewMember(),0,0,NoContainer(), Local(0)))) 
    if(GetAction(Local(0)) eq "Walk"||GetAction(Local(0)) eq "Idle"||GetAction(Local(0)) eq "Jump")
      return(Erstellen());
  return(1);

Erstellen:


  SetVar(1,CreateObject(HORS,0,-5,GetOwner(Local(0))));

  // Aufsitzen
  ObjectSetAction(Local(0),"Ride",Var(1));


  return(1);