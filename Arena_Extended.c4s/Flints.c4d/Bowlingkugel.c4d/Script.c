/*--- Kanonenkugel ---*/

#strict
#include PRNT

local alpha, cdelay, xdir, mul;

Check:
  SetAction("Exist");
  xdir = GetXDir();
  SetRDir(xdir);
  mul = 1;
  return(1);

Departure:
  xdir = GetXDir();
  SetRDir(xdir);
  return(1);

Hit:
  mul = 2;
  Sound("RockHit*");
  Sound("RockBreak*");
  return(1);

Entrance:
  SetOwner(GetOwner(Par(0)),this());
  return(1);

FadeOut:
  if(Contained()) cdelay=GetActTime();
  if(GetActTime() < 70+cdelay)
  {
    if(xdir)
    {
      SetXDir(xdir*mul);
      SetRDir(xdir);
      ObjectCall(CreateObject(0_F2,0,5,-1),"Start",GetR());
    }
    while(Var(0) = FindObject( 0, 0, -16, 20, 32, OCF_Living(),0,0,NoContainer(),Var(0)))
      if(GetOwner(Var(0)) != GetOwner())
      {
        DoEnergy(-20,Var(0));
        Fling(Var(0),Abs(GetXDir())/5,-2-Random(2));
      }
    while(Var(0) = FindObject( 0, -20, -16, 20, 32, OCF_Living(),0,0,NoContainer(),Var(0)))
      if(GetOwner(Var(0)) != GetOwner())
      {
        DoEnergy(-20,Var(0));
        Fling(Var(0),Abs(GetXDir())/-5,-2-Random(2));
      }
  }
  if(GetActTime()<70+cdelay || Contained() || Stuck()) return(0);
  alpha+=4;
  if(Random(10)) CreateParticle("PxSpark",-3+Random(6),-3+Random(6),0,0,10);
  SetClrModulation(RGBa(255,255,255,alpha));
  if(alpha>240) return(RemoveObject());
  return(1);