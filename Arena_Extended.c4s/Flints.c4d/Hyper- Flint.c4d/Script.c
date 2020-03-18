#strict
#include PRNT

//-MS-Flint-//

Hit:
for(var i = 0;i<10;i++) {
  SetVar(0,CreateContents(SH10));
  SetOwner(GetOwner(),Var(0));
  Exit(Var(0),0,0,Random(360), Sum(Random(10),-5), Sum(Random(2),-4), +10);
}
RemoveObject();
return(1);

Entrance:
  SetOwner(GetOwner(Par(0)),this());
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);

/* Forschung */

public GetResearchBase: return(EFLN);