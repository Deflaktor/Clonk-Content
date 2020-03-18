#strict
#include PRNT

NeededId:
  return(TFLN);
  
TurnTo:
  return(TSFT);

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
  SetLocal(0,CreateObject(SWE2,0,0,GetOwner()));
  ObjectSetAction(Local(0),"Implode");
  return(RemoveObject());

Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);
