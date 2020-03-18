#strict
#include PRNT

Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

Hit:
  CastObjectsX(SP58,10,300,0,-10,270,360,"Sett");
  Explode(18);
  return(1);

Activate:
  ObjectCall(Contained(),"Splitter");
  RemoveObject(this());
  return(1);

Sett:
  ObjectSetAction(Par(0),"Checking");
  SetOwner(GetOwner(), Par(0));
  return(1);