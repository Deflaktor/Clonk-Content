#strict

Initialize:
  SetAction("Blue");
  return(1);

public SetTargets:
  SetLocal(0,Par(0));
  SetLocal(1,Par(1));
  return(1); 

public Damage:
  Sound("Click");
  if(GetAction() S= "Blue")
    return(Green(Par(1)));
  if(GetAction() S= "Green")
    return(Blue(Par(1)));
  if(GetAction() S= "Red")
    return(Grey(Par(1)));
  return(1);

private Green:  
  SetAction("Grey");
  ObjectCall(Local(0),"ControlLeft");
  ObjectCall(Local(1),"ControlLeft");
  if(Local(0)&&!Local(1))
    SetPlrView(Par(0),Local(0));
  return(1);

private Blue:
  SetAction("Grey");
  ObjectCall(Local(0),"ControlRight");
  ObjectCall(Local(1),"ControlRight");
  if(Local(0)&&!Local(1))
    SetPlrView(Par(0),Local(0));
  return(1);

private Grey:
  SetAction("Grey");
  if(Local(0))
    SetPlrView(Par(0),Local(0));
  ObjectCall(CreateObject(EXPL,GetX(Local(0))-GetX(), GetY(Local(0))-GetY()),"Launch",40);
  ObjectCall(CreateObject(EXPL,GetX(Local(1))-GetX(), GetY(Local(1))-GetY()),"Launch",40);
  RemoveObject(Local(0));
  RemoveObject(Local(1));
  return(1);
