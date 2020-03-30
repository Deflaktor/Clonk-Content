#strict

local center;
local radius;
local an;

Start: 
  center=Par(0);
	radius=Par(1);
	SetPosition(GetX(center)+Par(1),GetY(center));
	for(var x=0; x<=radius/14; x++) 
		Local(0,CreateObject(CIRC,-GetX()+GetX(center)+14*x,0,-1))=x*14;
	SetCategory(C4D_StaticBack(), this());
	return(1);


func Movement() {
	if(center) {
		an++;
		while(Var(0)=FindObject(0,-16,-20,31,25,0,0,0,0,Var(0))) {
			SetPosition(-GetX()+GetX(Var(0))+GetX(center)+Cos(an,radius),-GetY()+GetY(Var(0))+GetY(center)+Sin(an,radius),Var(0));
		}
		Var(0)=0;
		while(Var(0)=FindObject(CIRC,0,0,0,0,0,0,0,0,Var(0)))
		  SetPosition(GetX(center)+Cos(an,Local(0,Var(0))),GetY(center)+Sin(an,Local(0,Var(0))),Var(0));
		
		SetPosition(GetX(center)+Cos(an,radius),GetY(center)+Sin(an,radius));		
		if(an==360) an=0;
	}
}

local x;
local xdir;

Start1:
  x=GetX();
	xdir=Par(0);
	SetAction("Sidemove");
	SetComDir(COMD_Left());
	return(1);
Side:
    if(GetX() > (x + xdir))
      SetComDir(COMD_Left());
    if(GetX() < (x - xdir))
      SetComDir(COMD_Right());
  return(1);


local y;
local ydir;

Start2:
  y=GetY();
	ydir=Par(0);
	SetAction("Upmove");
	SetComDir(COMD_Up());
	return(1);
Up:
    if(GetY() > (y + ydir))
      SetComDir(COMD_Up());
    if(GetY() < (y - ydir))
      SetComDir(COMD_Down());
  return(1);