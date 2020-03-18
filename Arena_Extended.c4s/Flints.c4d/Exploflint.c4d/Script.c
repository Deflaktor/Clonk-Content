#strict
#include PRNT

Check:
  SetAction("Delay");
  return(1);

Entrance:
  SetOwner(GetOwner(Par(0)));
  return(1);

Activate:
  SetOwner(GetOwner(Par(0)));
  return(Hit());

Hit:
  Local(0)++;
  if(Local(0)>5+Random(5)) {
    Explode(30);
  } else {
    Var(1)=2;
    while(SetVar(0,FindObject(0,0,0,-1,-1,OCF_Alive(),0,0,0,Var(0)))) if(CreateSplitter(Var(0))) if(Var(1)--<=0) return(1);
  }
  return(1);

CreateSplitter:
  if (GetOwner()==GetOwner(Par(0)))
    return(0);
  if (!GetAlive(Par(0)))
    return(0);
  CreateObject(PRNT,AbsX(GetX(Par(0))),AbsY(GetY(Par(0))),GetOwner())->Explode(10);
  CreateParticle("PxSpark", 0, 0,0,0,100, RGBa(50,50,200,10));
  return(1);