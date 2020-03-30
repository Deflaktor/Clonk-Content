#strict

local hej;

Activate:
if(GetCon(Par())!=100||FindObject(HTM4,AbsX(GetX(Par())),AbsY(GetY(Par()))))
  return(1);
  
Sound("Magic1");
CreateParticle("FSpark",GetX(Par())-GetX(),GetY(Par())-GetY()+20,0,-35, 500, RGBa(200,50,0,80,127));
//CastParticles("FSpark", 10,50, 0,0, 50, 200, RGBa(200,128,255,0), RGBa(127,255,255,127));

SetLocal(0,1000);
SetLocal(1,GetPhysical("Jump",2,Par()));
if(Local(1)==0)
  SetLocal(1,GetPhysical("Jump",1,Par()));

SetPhysical( "Jump", Sum(Local(1),Local()), 2,Par());

SetLocal(1,GetPhysical("Walk",2,Par()));
if(Local(1)==0)
  SetLocal(1,GetPhysical("Walk",1,Par()));

SetPhysical( "Walk", Sum(Local(1),Local()), 2,Par());

SetLocal(1,GetPhysical("Throw",2,Par()));
if(Local(1)==0)
  SetLocal(1,GetPhysical("Throw",1,Par()));

SetPhysical( "Throw", Sum(Local(1),Local()), 2,Par());

//SetLocal(0,0);

while(Local(3)<=18)
{
if(Not(Random(4)))
  Smoke();
SetLocal(3,Local(3)+1);
DoCon(1,Par());
}
SetLocal(6,Par());
SetAction("wait");
return(1);

check:
SetPosition(GetX(Local(6)),GetY(Local(6)));
if(SEqual(GetAction(Local(6)),"Jump"))
	hej=1;
if(hej)
	if(Not(SEqual(GetAction(Local(6)),"Jump"))){
		hej=0;
		Sound("BigHit");
		CreateParticle("wolke",GetX(Local(6))-GetX()-5,GetY(Local(6))-GetY()+20,90,0, 500, RGBa(200,50,50,80));
		CreateParticle("wolke",GetX(Local(6))-GetX()+5,GetY(Local(6))-GetY()+20,-90,0, 500, RGBa(200,50,50,80));
		if(!Random(10))
			LaunchEarthquake(GetX(),GetY());
		while(SetVar(0,FindObject(0,-40,-20,80,40,OCF_Living(),0,0,NoContainer(),Var())))
			if(Var()!=Local(6))
			{Punch(Var(),15); Sound("Kime*"); }
		}
return(1);

rem:
DoCon(-Local(3),Local(6));
SetLocal(1,GetPhysical("Jump",2,Local(6)));
SetPhysical( "Jump", Sub(Local(1),Local()), 2,Local(6));
SetLocal(1,GetPhysical("Walk",2,Local(6)));
SetPhysical( "Walk", Sub(Local(1),Local()), 2,Local(6));
SetLocal(1,GetPhysical("Throw",2,Local(6)));
SetPhysical( "Throw", Sub(Local(1),Local()), 2,Local(6));
RemoveObject();
return(1);