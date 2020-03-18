/*-- Neues Objekt --*/

#strict

protected Initialize:
  return(1);

Stop:
  SetPhysical("Walk", 0, 2, Par(0)); 
  SetPhysical("Jump", 0, 2, Par(0));
  SetPhysical("Float", 0, 2, Par(0));
  SetSpeed(0,0,Par(0));
  SetPosition(Local(4),Local(5),Par(0));
  return(1);

Release:
  SetPhysical("Walk", GetPhysical("Walk",1,Par(0)), 2, Par(0)); 
  SetPhysical("Jump", GetPhysical("Jump",1,Par(0)), 2, Par(0));
  SetPhysical("Float", GetPhysical("Float",1,Par(0)), 2, Par(0));
  if(Local(6))
    SetLocal(0,Local(6),Par(0));
  if(Local(7))
    SetLocal(1,Local(7),Par(0));
  SetSpeed(Local(2),Local(3),Par(0));
  SetLocal(69,0,Par(0));
  RemoveObject();
  return(1);

Help:
  if(!Local(0))
    RemoveObject();
  if(Local(0))
    Stop(Local(0));
  if(GetID(Local(0))==__DV)
    Release(Local(0));
  if(Distance(GetX(Local(1)), GetY(Local(1)), GetX(Local(0)), GetY(Local(0)))>GetCon(Local(1))/2)
    Release(Local(0));
  if(!Local(1))
    Release(Local(0));
  return(1);