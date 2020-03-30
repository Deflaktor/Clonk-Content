//von major}

#strict
local target,old;
public Activate:
 Sound("Wind2");
 
 target=Par();
 CastParticles("MSpark", 50,50, GetX(target)-GetX(),GetY(target)-GetY(), 20, 50, RGB(255), RGB(255));
  CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 1000, RGBa(255,50+Var(),50+Var(),100));
SetAction("inluft");
return(1);

rem:
Sound("Magic1");
enterluft();
RemoveObject();
return(1);

tick:
DoBreath(100*10-Local(), target);
SetPosition(GetX(target),GetY(target));
Local()=Local()+1;
if(Local()>850)
{
CreateParticle("MSpark", GetX(target)-GetX(),GetY(target)-GetY(), 0,-10, 100, RGBa(20,20,150,50));
}
if(Local()>1000)
  rem();
return();

enterwasser:
SetPhysical( "BreatheWater", 1, 2,target);
SetAction("inwasser");
return();

enterluft:
SetPhysical( "BreatheWater", 0, 2,target);
SetAction("inluft");
return();

checkinluft:
if(!InLiquid(target))
  enterluft();
return();

checkinwasser:
if(InLiquid(target))
  enterwasser();
return();

