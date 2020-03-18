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
  if(!Random(500))
    ChangeDef(S658);
  return(1);

NoShiftOwner:
  return(1);

RejectEntrance:
  if(GetOwner()!=GetOwner(Par(0)))
    return(0);
  return(1);

Hit:
  Sound("god");
  return(1);

Activate:
  if(GetOwner()==GetOwner(Par(0)))
    return(1);
SetWealth(GetOwner(Par(0)),Sum(GetWealth(GetOwner(Par(0))),5));
Sound("Frag");
CastObjects(SPRK,5,28);
RemoveObject(this());
  return(1);

Delete:
  Sound("god");
  RemoveObject(this());
  return(1);

Destroy:
SetWealth(Par(0),GetWealth(Par(0))+5);
return(0);

Check:
  return(1);
