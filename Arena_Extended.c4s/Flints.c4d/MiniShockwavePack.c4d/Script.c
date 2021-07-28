#strict
#include PRNT

NeededId:
  return(_RND);
  
TurnTo:
  if(!Random(10))
    return(SHB4);
  return(SHB3);

Activate:
  if(Not(SetVar(0,FindObject(NeededId(),-1,-1,2,2,0,0,0,Contained(),0))))
    return(MessageError());
  if(Var(0)==this())
    return(MessageError());
  RemoveObject(Var(0));
  Sound("Connect");
  ChangeDef(TurnTo());
  this()->Redefine();
  return(1);

MessageError:
  Sound("NoAmmo");
  Message(Format("Es fehlt noch ein %s", GetName(0, NeededId())), this());
  return(1);

Hit:
  for(var i=0;i<10;i++)
    CastObjectsX(SHFT,4,50+Random(50),0,-10,270,180,"Sett");
  Explode(30);
  return(1);

Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

Sett:
  ObjectSetAction(Par(0),"Checking");
  SetOwner(GetOwner(), Par(0));
  return(1);