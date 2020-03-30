//vom major}

#strict

local ziel;

public Activate:
 Sound("Flash");
  CreateObject(_FLS,0,0,-1)->Activate();
  while(SetVar(0,FindObject(0,-500,-500,1000,1000,OCF_CrewMember(),0,0,NoContainer(),Var())))
       if(Hostileto(GetOwner(Var()),GetOwner(Par())))
	   dmg(Var());


return(RemoveObject());


private func dmg(target)
{
var nx;
nx=CreateObject(GetID(),0,0,GetOwner(target));
ObjectCall(nx,"targetx",target);
return(1); 
}



wolke:
SetPosition(GetX(ziel),GetY(ziel));
return(1);

targetx:
ziel=Par();
//SetFoW (1,GetOwner(ziel)); 
SetPlrViewRange (3+Random(3),ziel); 
SetAction("blend");
return(1);

rem:
Sound("Magic1");
SetPlrViewRange (1000,ziel); 
CreateParticle("wolke", GetX(ziel)-GetX(),GetY(ziel)-GetY(), 0,-10, 500, RGBa(0,RandomX(0,20),255,80));  
RemoveObject();
return();  