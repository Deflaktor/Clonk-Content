/*-- Melone --*/

#strict
#include PRNT


Check:
  SetAction("Delay");
  return(1);

public func Activate(object pClonk)
{
  [Essen|Image=MELO]
  Eat(pClonk);
  return(1);
}

public func Eat(object pClonk)
{
  DoEnergy(80, pClonk);
  CastObjects(MELS,1,10,0,-2);
  CastObjects(BLUT,25,30,0,-1);
  Sound("ClonkMunch");
  RemoveObject();
  return(1);
}

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) DamageIt(Var(0));
  return(1);
  
DamageIt:
  Punch(Par(0),20);
  Hit();
  return(1);

public func Hit() {
  CastObjects(MELS,2,50,0,-2);
  CastObjects(BLUT,35,50,0,-1);
  Sound("CROCBITE");
  RemoveObject();
}