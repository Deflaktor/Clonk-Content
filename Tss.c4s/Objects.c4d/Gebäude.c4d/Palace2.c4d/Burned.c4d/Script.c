#strict

protected Construction:
  SetLocal(9,CreateObject(BAS9,0,+8));
  return(1);
  
protected Destruction:
  if (Local(9)) RemoveObject(Local(9));
  return(1);

