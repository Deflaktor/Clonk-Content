/*-- Schulden --*/

#strict

Initialize:
  SetLocal(2,0);
return(0);

protected ChangeMoney:
  if(Not(Equal(GetCon(Local(1)),100)))
    return(1);
  if(And(Equal(Local(2),250),Local(1)))
    return(1);
  if(Local(1))
    SetLocal(2,Sum(Local(2),1));
  if(Local(1))
    SetWealth(GetOwner(this()),Sum(GetWealth(GetOwner(this())),1));
  if(Local(1))
    return(0);

  if(Equal(Local(2),0))
    RemoveObject(0);

  if(Equal(GetWealth(GetOwner(this())),0))
    return(0);
  SetLocal(2,Sub(Local(2),1));
  SetWealth(GetOwner(this()),Sub(GetWealth(GetOwner(this())),1));

  if(Equal(Local(2),0))
    RemoveObject(0);

  if(Equal(GetWealth(GetOwner(this())),0))
    return(0);
  SetLocal(2,Sub(Local(2),1));
  SetWealth(GetOwner(this()),Sub(GetWealth(GetOwner(this())),1));

  if(Equal(Local(2),0))
    RemoveObject(0);

  if(Equal(GetWealth(GetOwner(this())),0))
    return(0);
  SetLocal(2,Sub(Local(2),1));
  SetWealth(GetOwner(this()),Sub(GetWealth(GetOwner(this())),1));

  if(Equal(Local(2),0))
    RemoveObject(0);

  if(Equal(GetWealth(GetOwner(this())),0))
    return(0);
  SetLocal(2,Sub(Local(2),1));
  SetWealth(GetOwner(this()),Sub(GetWealth(GetOwner(this())),1));

  if(Equal(Local(2),0))
    RemoveObject(0);

  if(Equal(GetWealth(GetOwner(this())),0))
    return(0);
  SetLocal(2,Sub(Local(2),1));
  SetWealth(GetOwner(this()),Sub(GetWealth(GetOwner(this())),1));

  return(0);
