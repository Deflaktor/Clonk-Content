#strict

Initialize:
  Local(0)=-1;
  Local(1)=-1;
  Local(2)=-1;
  Local(3)=-1;
  Local(4)=-1;
  Local(5)=-1;
  Local(6)=-1;
  if(GetOwner()!=-1)
    Local(GetOwner()/32)=~(1<<(GetOwner()%32));
  SetVisibility(VIS_God() | VIS_Local());
  SetAction("Timer");
  return(1);

NoShiftOwner:
  return(1);

RejectEntrance:
  if(GetOwner()!=GetOwner(Par(0)))
    return(0);
  return(1);


Hit:
  Sound("god2");
  return(1);

Activate:
  if(GetOwner()==GetOwner(Par(0)))
    return(1);
  CastObjects(ST58,10,100);
  CreateObject(PRNT,0,0,GetOwner(Par(0)))->Explode(30);
  Sound("Frag2");
  return(RemoveObject());

Delete:
  Sound("god2");
  RemoveObject(this());
  return(1);

Destroy:
SetWealth(Par(0),GetWealth(Par(0))+5);
return(0);

Check:
  return(1);
