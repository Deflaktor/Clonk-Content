#strict
local ziel;

Activate:
Sound("Boing");
ziel=Par();
ObjectSetAction(ziel,"Jump"); 
SetPosition(GetX(ziel),GetY(ziel)-1,ziel);
SetYDir(-75,ziel);
SetAction("Fly");
if(GetDir(ziel))
	{SetXDir(50,ziel);
	return(1);}
SetXDir(-50,ziel);
return();


flug:
//SetPosition(GetX(ziel),GetY(ziel));
if(GetActTime()>100)
	return(RemoveObject());
if(Abs(GetXDir(ziel))<3)
	return(RemoveObject());
CastParticles("wolke", 50,50, GetX(ziel)-GetX(),GetY(ziel)-GetY(), 2, 15, RGB(100), RGB(255));
 CreateParticle("wolke", GetX(ziel)-GetX(),GetY(ziel)-GetY(), 0,-10, 500, RGBa(0,RandomX(50,150),50,80));

//CastParticles("FSpark", 10,50, GetX(ziel)-GetX(),GetY(ziel)-GetY(), 100, 200, RGBa(200,10,20,0), RGBa(255,255,255,200));
//CreateParticle("MSpark", GetX(ziel)-GetX(),GetY(ziel)-GetY(),-50, 500, RGBa(255,255,255,45));

  return(1);
