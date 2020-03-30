#strict

local anzahl;

protected func Initialize()
{ anzahl=ObjectCount(ZPKI);
  SetAction("Fly");
  return(1); }   

private func ReproductionControl()
{
if(!FindObject(ZPKI))
	return();
if(ObjectCount(ZPKI)>=anzahl)
	return();
SetPosition(Random(LandscapeWidth())-1,Random(LandscapeHeight())-1);
Var()=FindObject(ZPKI,0,0,-1,-1);
Var()->ReproductionX();
return();
}