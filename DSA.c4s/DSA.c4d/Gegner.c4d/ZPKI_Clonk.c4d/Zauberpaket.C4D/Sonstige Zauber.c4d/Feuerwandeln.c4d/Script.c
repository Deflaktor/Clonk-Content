//von major}

#strict
local target,i,step;

public Activate:
step=10;
 Sound("Wind2");
 
 target=Par();
 CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(255), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(255,50+Var(),50+Var(),100));
SetAction("schutz");
return(1);

rem:
Sound("Magic1");
RemoveObject();
return(1);

psch:
SetPosition(GetX(target),GetY(target));
if(OnFire(target))
	Extinguish(target);
i=i+step;
if(i>360-step)
	i=0;


CreateParticle("MSpark",Cos(i,13),Sin(i,13),Cos(i),Sin(i), 100, RGBa(255,50+Var(),50+Var(),100));

return();