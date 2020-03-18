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
Message("Monstergeddon überstanden!");
return(RemoveObject());

	Explosion:

SetVar(0,CreateObject( MONS, Random(LandscapeWidth()) , -100+Random(100), -1) );
if(Random(2)) 
  Var(0)->SetFeuerMonster();
SetXDir(Sub(200,Random(400)),Var(0));
SetYDir(Sub(2000,Random(500)),Var(0));
return(1);