/*-- Neues Objekt --*/

#strict

protected Initialize:
  return(1);

Stop:
  SetPhysical("Walk", GetPhysical("Walk",1,Par(0))/10, 2, Par(0)); 
  SetPhysical("Jump", GetPhysical("Jump",1,Par(0))/10, 2, Par(0));
  SetPhysical("Float", GetPhysical("Float",1,Par(0))/10, 2, Par(0));
  SetVar(1,GetXDir(Par(0)));
  SetVar(2,GetYDir(Par(0)));
  if(!Local(4))
    if(Var(2)<10||Var(2)>-10)
      SetLocal(4,GetY(Par(0)));
  if(Local(4))
    SetPosition(GetX(Par(0)),Local(4),Par(0));
  SetSpeed(Var(1)/10,Var(2)/10,Par(0));
  if(SEqual(GetAction(Par(0)),"Travel")) {
    // Merke alte Geschwindigeit um nacher rückzusetzen
    if(!Local(2))
    SetLocal(2,Local(0,Par(0)));
    if(!Local(3))
    SetLocal(3,Local(1,Par(0)));
    // Verlangsamen
    SetLocal(0,Var(1)/20,Par(0));
    SetLocal(1,Var(2)/20,Par(0));
  }
  //if(GetOCF(Par(0)) & OCF_Alive())
  //  DoEnergy(-1,Par(0));
  return(1);

Release:
  SetPhysical("Walk", GetPhysical("Walk",1,Par(0)), 2, Par(0)); 
  SetPhysical("Jump", GetPhysical("Jump",1,Par(0)), 2, Par(0));
  SetPhysical("Float", GetPhysical("Float",1,Par(0)), 2, Par(0));
  SetLocal(0,Local(2),Par(0));
  SetLocal(1,Local(3),Par(0));
  SetLocal(69,0,Par(0));
  RemoveObject();
  return(1);

Help:
  if(Local(0))
    Stop(Local(0));
  if(Distance(GetX(Local(1)), GetY(Local(1)), GetX(Local(0)), GetY(Local(0)))>GetCon(Local(1)))
    Release(Local(0));
  if(!Local(1))
    Release(Local(0));
  return(1);