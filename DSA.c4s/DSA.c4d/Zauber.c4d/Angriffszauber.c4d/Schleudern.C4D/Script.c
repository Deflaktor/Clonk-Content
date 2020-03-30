//Author:major}

#strict

local y,owner;

CastMeteor:
  Sound("Inflame");
  if (GetComDir() == COMD_Left()) CastLeft();
  if (GetComDir() == COMD_Right()) CastRight();
  return(1);

CastRight:
  SetLocal(0,+100);
  SetXDir(30,SetLocal(1,CreateObject(HH07,20,-5)));
  SetYDir(-35,Local(1));
  SetAction("Travel");
  SetPlrView (owner,Local(1));
  ObjectCall(Local(1),"go",DIR_Right());
  Local(1)->Effekt();
  return(1);

CastLeft:
  SetLocal(0,-100);
  SetXDir(-30,SetLocal(1,CreateObject(HH07,-20,-5)));
  SetYDir(-35,Local(1));
  SetAction("Travel");
  SetPlrView (owner,Local(1));
  ObjectCall(Local(1),"go",DIR_Left());
  Local(1)->Effekt();
  return(1);

Activate:
  owner=GetOwner(Par());
  if (GetDir(Par(0))==DIR_Left()) SetComDir(COMD_Left());
  if (GetDir(Par(0))==DIR_Right()) SetComDir(COMD_Right());
  SetAction("Travelw");
  ObjectSetAction(Par(),"Throw");
  y=GetY(Local(1));
  return(1);

Travel:
var els;
els=1;

  if(!Local(1))
     return(RemoveObject());
SetPosition(GetX(Local(1)),GetY(Local(1)));



if(GetDir(Local(1))==DIR_Right())
	CreateParticle("MSpark",3,0,0,0, 80, RGBa(200+RandomX(-55,55),150+RandomX(-55,55),50,80));
if(GetDir(Local(1))==DIR_Left())
	CreateParticle("MSpark",-3,0,0,0, 80, RGBa(200+RandomX(-55,55),150+RandomX(-55,55),50,80));

  // CastParticles("wolke", 50,50,GetX(Local(1))-GetX(),GetY(Local(1))-GetY(), 8, 15, RGB(100), RGB(255));
  //CastParticles ("MSpark",15,80,AbsX(GetX(Local(1))),AbsY(GetY(Local(1))),7,9,RGBa(255,Random(50),Random(50),100),RGBa(255,0,0,0)); 
  //CreateParticle ("MSpark",AbsX(GetX(Local(1))),AbsY(GetY(Local(1))),Local(),10,8,RGBa(200,0,0,15));

  SetXDir(Local(0),Local(1));
  
 	 SetYDir(Abstand((Random(60)-30)),Local(1));
return(1);

private func Abstand(par)
{
if(GetYDir(Local(1))<10&&par<0)
	par=par+10;
return(par);
}

private func minusoderplus(zahl)
{
if(zahl>0)
	return(1);
return(-1);
}