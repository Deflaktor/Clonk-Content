// MSC-Script //

#strict
#include PRNT

/*-- short residue --*/

Hit:
  GameCall("RestoreMapInstantly");
  Explode(30, CreateObject(FLNT));
  while(Var(0)<=360) {
    Var(1) = CreateObject(MSHF,Sin(Var(0),7),-Cos(Var(0),7),GetOwner());
    SetSpeed(Sin(Var(0),100),-Cos(Var(0),100), Var(1));
    Var(0)+=10;
    CastObjects(SPRK, 15, Var(0));
  }

  RemoveObject();
  return(1);

