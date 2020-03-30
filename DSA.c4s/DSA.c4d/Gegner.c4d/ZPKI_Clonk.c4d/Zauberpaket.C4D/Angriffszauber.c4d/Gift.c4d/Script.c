//vom major}

#strict

local ziel,nt;

public Activate:
 Sound("Magic1");
  
  while( SetVar(0,FindObject(0,-500,-500,1000,1000,OCF_CrewMember(),0,0,NoContainer(),Var())))
       if(Hostileto(GetOwner(Var()),GetOwner(Par())))
          dmg(Var());


return(RemoveObject());


private func dmg(target)
{
Sound("Snuff*");
var nx;
nx=CreateObject(GetID(),0,0,GetOwner(target));
ObjectCall(nx,"targetx",target);
return(1); 
}



wolke:
if(InLiquid(ziel))
	return(rem());
SetPosition(GetX(ziel),GetY(ziel));
if(!ziel||GetEnergy(ziel)==0)
	return(RemoveObject());

  CastParticles("MSpark", 50,50, GetX(ziel)-GetX(),GetY(ziel)-GetY(), 2, 15, RGB(100), RGB(255));
if(nt--<0){ nt=2;
  CreateParticle("gift", GetX(ziel)-GetX(),GetY(ziel)-GetY(), 0,0, 500, RGBa(200,RandomX(5,15),50,80));}
return(1);

targetx:
ziel=Par();
SetAction("gift");
return(1);

schaden:
DoEnergy(-1,ziel);
return(1);

rem:
CreateParticle("wolke", GetX(ziel)-GetX(),GetY(ziel)-GetY(), 0,-10, 500, RGBa(20,RandomX(0,20),255,80));  
RemoveObject();
return();   