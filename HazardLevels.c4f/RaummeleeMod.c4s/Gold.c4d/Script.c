#strict

Entrance:
  if(GetID()==_GVK)
    SetWealth(GetOwner(Par(0)),Sum(GetWealth(GetOwner(Par(0))),((GetValue()+Local(3,Par(0)))*(100+20*Local(17,Par(0))))/100));
  else
    SetWealth(GetOwner(Par(0)),Sum(GetWealth(GetOwner(Par(0))),GetValue()));
  Sound("Uncash");
  if(ObjectCount(SPRK)<300)
    CastObjects(SPRK,GetValue(),28);
  RemoveObject(this());
  return(1);
  
NoCollectLimit:
  return(1);
  
RejectEntrance:
  return(GetID(Par(0))==HK00);