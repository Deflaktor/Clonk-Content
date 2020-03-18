// Local 0: XDir
// Local 1: YDir
// Local 2: Zeit bis Removen

#include PRNT

NoShiftOwner:
  return(1);

Hit:
  Sound("Plumps");
  return(SetAction("CauseDamage"));

Dangerous:
  while(SetVar(0,FindObject(0,-80,-80,160,160,OCF_Living(),0,0,NoContainer(),Var(0)))) Harm(Var(0));
  if(GreaterThan(GetActTime(this()),700)) return(RemoveObject());
  return(1);

Harm:
  if(GetOwner(Par(0))==GetOwner())
    return(1);
  DoEnergy( Div(Sum(Mul(80,-1),ObjectDistance(Par(0))),30) , Par(0) );
  return(1);

Damage: 
return(RemoveObject());