//Locals  0Owner   1KI   2Counter
#strict

Initialize:
SetOwner(-1);
SetPosition(0,0);
Start();
return(1);

	Start:
SetAction("Los");
return(1);

	Remove:
Message("Armageddon überstanden!");
return(RemoveObject());

	Explosion:
SetVar(0,CreateObject(METO,Random(LandscapeWidth()),Sub(1,Sum(100,Random(100)))));
SetXDir(Sub(100,Random(200)),Var(0));
SetYDir(Sub(200,Random(50)),Var(0));
return(1);