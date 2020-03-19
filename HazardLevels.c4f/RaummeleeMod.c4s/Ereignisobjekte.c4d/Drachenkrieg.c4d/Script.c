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
  Message("Drachenkrieg vorbei!");
  return(RemoveObject());

Explosion:
  while(Var(0)=FindObject(0,0,0,0,0,0,0,0,NoContainer(),Var(0))) {
    if(ObjectCall(Var(0),"IsProjectile")) {
	  if(GetID(Var(0))!=DA1D)
	    ChangeDef(DA1D,Var(0));
	}
  }
  return(1);