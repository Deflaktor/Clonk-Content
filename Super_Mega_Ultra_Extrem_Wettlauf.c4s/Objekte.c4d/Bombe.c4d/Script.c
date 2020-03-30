#strict

/**********************\
* BOMBERMAN C          *
* by Clonkitator 2002  *
\**********************/

Initialize:
  SetAction("TIKTAK");
  return(1);

Remove:
  RemoveObject();
  return(1);
  
CheckGround:
  if (SetVar(0,FindObject(BIK1,-20,-30,40,50)))
  Boom(Var(0));
  if (SetVar(0,FindObject(CLNK,-20,-20,40,40,0,0,0,NoContainer())))
  Boom(Var(0));
  return(1);
  
Boom:
  ObjectCall(CreateObject(WP3V),"Launch",50);
  ObjectCall(Par(),"Destroy");
  return(1);

IsSolid: return(1);