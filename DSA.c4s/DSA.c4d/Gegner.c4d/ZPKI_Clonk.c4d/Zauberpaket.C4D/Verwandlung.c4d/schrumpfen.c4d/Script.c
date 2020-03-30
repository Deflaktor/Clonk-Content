#strict
local target;

func Activate(ziel){
if(!(GetOCF(ziel)&OCF_CrewMember())||GetCon(Par())!=100)
	return();
target=ziel;
if(GetCon(Par())<100||FindObject(HHZ1,AbsX(GetX(Par())),AbsY(GetY(Par()))))
  return();
Sound("Magic1");
CreateParticle("MSpark",GetX(Par())-GetX(),GetY(Par())-GetY()-20,0,+35, 500, RGBa(0,200,50,80));
SetLocal(0,0);

DoCon(-50,target);

SetAction("wait",target);
return(1);}

func rem(){
DoCon(+50,target);
RemoveObject();
return(1);}

private func wachs()
{
DoCon(+5,target);
if(GetCon(target)==100)
	return(RemoveObject());
}