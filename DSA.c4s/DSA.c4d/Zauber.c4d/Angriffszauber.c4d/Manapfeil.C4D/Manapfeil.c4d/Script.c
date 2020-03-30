#strict

//von meteor aber stark verändert ^^

protected func SmokeTrail() {
CastParticles("FSpark", 10,50, 0,0, 100, 200, RGBa(200,128,255,0), RGBa(127,255,255,127));

 if (Or(FindObject(0,-12,-13,24,26,OCF_Prey(),0,0,NoContainer()),
         FindObject(0,-12,-13,24,26,OCF_Prey(),0,0,NoContainer()))) Hit();

  //Smoke(0, 0, 5);
  //Smoke(0, -5, Random(7));
  var i = Random(50);
  while (i--) {
    var c = 20+Random(41);
    CreateParticle("PxSpark", Random(11)-5, Random(11)-5, 0, 0, c,
      RGBa(Random(100), 0, 255, c*4, 128));
  }
  CreateParticle("PxSpark", 0, 0, 0, 0, 20,
    RGBa(155, 255, 0, 128));
}

public func Completion() {
 
  SetAction("Evaporate");
}

protected func Hit() {
for(var i;i<=360;i=i+10)
	CreateParticle ("PxSpark",Cos(i,2),Sin(i,2),Cos(i,50),Sin(i,50),20,RGBa(Random(40),180,180,120)); 

for(i=5;i<=360;i=i+10)
	CreateParticle ("PxSpark",Cos(i,2),Sin(i,2),Cos(i,50),Sin(i,50),20,RGBa(180,Random(40),80,120)); 

CreateParticle("Blast", 0,0, 0,0, 300, RGBa(200,50,20,0));

while(Var()=FindObject(0,-19,-19,39,39,OCF_Living(),0,0,NoContainer(),Var())){SetPosition(GetX(Var()),GetY(Var())-2,Var());
	DoEnergy(-20+Random(5),Var()); PrivateCall(Var(),"Hurt"); Fling (Var(),(GetXDir()/200)*5,-5);}

RemoveObject();
}
