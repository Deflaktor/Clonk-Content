#strict

//von meteor leicht abgewandelt

local main;



protected func psch()
{
Sound("Pshshsh");
return(Hit());
}

protected func SmokeTrail() {
  Smoke(0, 0, 5);
  Smoke(0, -5, Random(7));
  var i = Random(50);
  while (i--) {
    var c = 20+Random(41);
    CreateParticle("PxSpark", Random(11)-5, Random(11)-5, 0, 0, c,
      RGBa(255, Random(70), 0, c*4, 128));
  }
  CreateParticle("PxSpark", 0, 0, 0, 0, 20,
    RGBa(200, 155, 0, 128));
}

public func go(dir) {
  dir=!dir;  //Hab Grafiken ausversehn falschrum gemacht ^_^
   SetAction("Fly");
    main=1;
  SetDir(dir);
   }

protected func Hit() {
if(!main)
	return(Explode(5));
CastObjects(DFLM,3,50);
Fetzen(4+Random(1));
Explode(20+RandomX(-5,5));
}

private func Fetzen(anzahl)
{
for(var i;i<=anzahl;i++)
{
Var()=CreateObject(GetID());
Var()->klein();
SetXDir(RandomX(-30,30),Var());
SetYDir(RandomX(-30,-60),Var());
}

return(anzahl);
}

public func Effekt(){
SmokeTrail();

  if(Var()=FindObject(0,-12,-13,24,26,OCF_Living(),0,0,NoContainer(),Var()))
	if(GetAlive(Var()))
		 return(Hit());

CastParticles ("PxSpark",10,20,0,0,20,23,RGBa(200,Random(200),12,125),RGBa(255,255,255,125)); 
return(1);
}

public func klein()
{
SetAction("klein");
return(DoCon(-75));}


