/*-- Blue Battery --*/

#strict
#appendto _AP0

RejectEntrance:
  if(Local(0))
    if(GetOwner()!=GetOwner(Par(0)))
      return(1);
  return(_inherited());
  
Entrance:
  if(Local(0)) {
    SetOwner(-1);
	SetVisibility(VIS_All());
	Local(0)=0;
  }
  return(_inherited());