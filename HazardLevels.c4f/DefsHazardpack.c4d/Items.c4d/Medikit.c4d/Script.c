#strict

Hit:
  Sound("RockHit");
  return(1);
Activate:
  if(Var(0)=GameCall("MedkitHeal"))
    DoEnergy(+Var(0),Par(0));
  else
    DoEnergy(+50,Par(0));
  Extinguish(Par(0));
  if(Var(0)=FindObject(_SIP))
    if(Local(0,Var(0))==Par(0))
      SetLocal(1,1,Var(0));
  while(Var(0)=FindObject(_SIE,0,0,0,0, 0,0,Par(0),0,Var(0)))
    Var(0)->Remove();
  Sound("Heal");
  RemoveObject();
  return(1);
