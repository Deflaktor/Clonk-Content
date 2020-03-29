#strict

Initialize:
  SetAction("gaglguglgigl");
  return(1);

Damage:
  if(GetDamage()>=30)
    return(SetAction("Kaputt"));
  return(1);
  
BiipBiip:
  if(!CheckEnergy())
    return(1);
  SetAction("Aufmachen");
  return(1);

Peeeeeeeeeeeeeeeng:
  if(Random(2))
    Var(0)=CreateObject(SHRP,-10+Random(20),10);
  if(Random(2))
    Var(0)=CreateObject(SHRD,-10+Random(20),10);
  var rand = Random(4);
  if(rand==0)
    Var(0)=CreateObject(_TF1,-2+Random(4),30);
  if(rand==1)
    Var(0)=CreateObject(_TF2,-2+Random(4),20);
  if(rand==2)
    Var(0)=CreateObject(_DF1,-2+Random(4),10);
  if(rand==3)
    Var(0)=CreateObject(_DF2,-2+Random(4),10);
  SetR(-20+Random(60),Var(0));
  SetXDir(-5+Random(10),Var(0));
  SetYDir(Random(5),Var(0));
  if(Random(2)) {
    Var(0)=CreateObject(_DF1,10,10);
    SetR(-20+Random(60),Var(0));
  }
  if(Random(2)) {
	Var(0)=CreateObject(_DF2,-10,10);
	SetR(-20+Random(60),Var(0));
  }
  return(1);
  
  
CheckEnergy:
  if (Not(GameCall("MainEnergySupply", this()))) return(0);
return(1);
