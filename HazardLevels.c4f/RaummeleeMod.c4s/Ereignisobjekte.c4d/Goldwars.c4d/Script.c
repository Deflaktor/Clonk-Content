#strict

Initialize:
  SetOwner(-1);
  SetPosition(0,0);
  Start();
  return(1);

Start:
  SetAction("Los");
  return(1);

Remove:
  Message("Goldkrieg vorbei!");
  return(RemoveObject());

Explosion:
  while(Var(0)=FindObject(0,0,0,0,0,0,0,0,NoContainer(),Var(0))) {
    if(ObjectCall(Var(0),"IsProjectile")) {
	  ChangeDef(_GVP,Var(0));
	}
  }
  return(1);