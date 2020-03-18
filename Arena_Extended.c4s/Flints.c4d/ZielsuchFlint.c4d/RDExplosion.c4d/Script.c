//Locals  0Owner   1KI   2Counter
#strict
	Start:
Explode(35,CreateObject(PRNT,0,30,GetOwner()));//Anfangsexplosion
SetAction("Los");
return(1);

	Remove://fette Explosion am schluss
while(LessThan(Local(2),10)) FinalEXPL();
return(RemoveObject());

	FinalEXPL:
SetVar(0,CreateObject(PRNT,Sum(-40, Random(80)),Sum(-12, Random(75))));
Explode(70,Var(0));
SetLocal(2,Sum(Local(2),1));
return(1);


	Explosion://Explosionen in der mitte der Explosionskette
//Explode(Random(20)+10,CreateObject(PRNT,Sum(-10, Random(20)),Sum(-10, Random(20))));
//Explode(Random(20)+10,CreateObject(PRNT,Sum(-20, Random(40)),Sum(-20, Random(40))));
//Explode(Random(20)+10,CreateObject(PRNT,Sum(-35, Random(70)),Sum(-35, Random(70))));
//Explode(Random(20)+10,CreateObject(PRNT,Sum(-60, Random(120)),Sum(-80, Random(140))),);
Explode(Random(20)+10,CreateObject(PRNT,-30+Random(60),-40+Random(80)) );
return(1);
