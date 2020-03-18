#strict

Init:
  SetOwner(Par(0));
  SetCrewEnabled(0);
  SetAction("Active");
  SetAlive(0);
  return(1);

Remove:
  if(Var(1)=FindObject(MNTK)) {
    if(Var(1)=Var(1)->GetNoRespawn()) {
      return(1);
    }
  }
  ChangeDef(CLON);
  GameCall("RelaunchPlayer",GetOwner(),this());
  return(1);
  
Damaged:
  return(1);
  
IsGodMode:
 return(false);

Destroy:
  return(1);