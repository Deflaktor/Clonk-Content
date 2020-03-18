#strict
#include PRNT

ExplodeSize:
  return(18);
  
NeededId:
  return(GetID());
  
TurnTo:
  return(SFLN);

Hit:
  Explode(ExplodeSize());
  return(1);

Redefine:
  if(Contained())
    while(ScrollContents(Contained())!=this()) {}
  return(1);
  
Activate:
  if(Not(SetVar(0,FindObject(NeededId(),-1,-1,2,2,0,0,0,Contained(),0))))
    return(MessageError());
  if(Var(0)==this())
    return(MessageError());
  Sound("Connect");
  RemoveObject(Var(0));
  ChangeDef(TurnTo());
  this()->Redefine();
  return(1);

MessageError:
  Sound("NoAmmo");
  Message(Format("Es fehlt noch ein %s", GetName(0, NeededId())), this());
  return(1);
  
Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);
