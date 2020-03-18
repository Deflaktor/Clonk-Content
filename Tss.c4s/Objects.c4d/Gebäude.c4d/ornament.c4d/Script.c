/*-- Ziergebäude --*/

#strict

/* Fundament (Local 9) */

protected Construction:
  SetLocal(7,CreateObject(BAS2,0,+8));
  CreateObject(DEBT,0,0,GetOwner(this()));
  SetLocal(1,this(),FindObject(DEBT,0,0,-1,-1));
  return(1);
  
protected Destruction:
  if (Local(7))
    RemoveObject(Local(7));
  return(1);

public GetResearchBase:
  return(GLA1);