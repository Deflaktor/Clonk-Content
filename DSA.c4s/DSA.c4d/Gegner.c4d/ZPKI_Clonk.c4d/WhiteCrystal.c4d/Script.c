#strict

protected func Hit()
{
Sound("Crystal*");
CastParticles("MSpark", 10,50, 0,0, 100, 200, RGBa(200,10,20,0), RGBa(255,255,255,200));
}

protected func Incineration()
{
Sound("Crystal*");
CastParticles("FSpark", 10,50, 0,0, 100, 200, RGBa(200,10,20,0), RGBa(255,255,255,200));
CreateParticle("Smoke", 00, 0,-50, 500, RGBa(255,255,255,45));
RemoveObject();
}

func check()
{
Var()=Contained();
if(!Var())
	return();
if(Var(1)=FindContents(HTZ0,Var())){
	Sound("Magic1");
	for(var i;i<100;i++)
		Var(1)->HTZ0::recharge();
	Hit();
	RemoveObject();}



}


