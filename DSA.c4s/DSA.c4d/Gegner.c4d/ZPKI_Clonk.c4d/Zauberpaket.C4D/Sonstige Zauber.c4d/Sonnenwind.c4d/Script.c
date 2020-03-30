//von major}

#strict

public Activate:

 Sound("Wind2");
 var target;
 target=Par();
 CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(255), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(255,50+Var(),50+Var(),100));

var lh;
var lw;
lh=LandscapeHeight();
lw=LandscapeWidth();
for(var i;i<=lw;i=i+5)
	CreateParticle ("wolke", i-GetX(),Random(lh)-GetY(), 30-IfRandom(2,60), 5, 80, RGBa(255,10,10,20)); 


SetTemperature(100);
return(RemoveObject());

global func IfRandom(izahl,iretvalue)
{
if(!Random(izahl))
	return(iretvalue);
}