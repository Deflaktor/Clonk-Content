#strict

local oldpwr,target;

func Activate(ziel)
{
if(FindObject(GetID(),0,0,0,0,0,"wait",ziel)){ Message("Nur 1x gleichzeitig anwendbar",target);
	return(RemoveObject());}

CreateParticle ("wolke",0,0,0,-5,130,RGBa(200,10,10,50)); 
Sound("Magic1");
SetAction("wait",ziel);
target=ziel;
oldpwr=GetCurrentPhysical("Fight",target);
//SetPhysical ("Fight", oldpwr*2, 2, target); 

ChangeDef(KRRA,target);
ObjectCall(target,"Redefine");

}


func rem()
{
Sound("Magic1");
CreateParticle ("wolke",0,0,0,-5,130,RGBa(10,10,200,50)); 
//SetPhysical ("Fight", oldpwr, 2, target); 
ChangeDef(KR3A,target);
ObjectCall(target,"Redefine");
RemoveObject();
}

global func GetCurrentPhysical(szPhysical,pObj)
{
Var()=GetPhysical (szPhysical,2,pObj); 
if(!Var())
	Var()=GetPhysical (szPhysical,1,pObj); 
return(Var());
}


