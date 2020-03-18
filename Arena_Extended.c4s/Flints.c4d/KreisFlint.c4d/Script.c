#strict
#include PRNT

/*-- T-Flint --*/

Initialize:
  if(FindObject(SRKR)) {
    ChangeDef(GameCall("Zufallsflint2"));
    return(ObjectCall(this(),"Initialize"));
  }
SetAction("Healing");
return(1);

/* Aufschlag */

GetSaugRadius:
  return(144);

Hit:
while(SetVar(1,FindObject(0,-GetSaugRadius(),-GetSaugRadius(),GetSaugRadius()*2,GetSaugRadius()*2,0,0,0,NoContainer(),Var(1))))
{
  if(GetOCF(Var(1)) & OCF_Living())
  {
    if (Distance(GetX(),GetY(),GetX(Var(1)),GetY(Var(1)))<GetSaugRadius()) 
    {
      DoEnergy(+100,Var(1));
      CreateParticle("PxSpark",-GetX()+GetX(Var(1)),-GetY()+GetY(Var(1)),0,0,150,RGBa(255,100,180,100));
    }
  }
}
Sound("Saug");
for(var angle=0; angle<360; angle+=1152/GetSaugRadius())
{ 
  CreateParticle("PxSpark", Sin(angle, GetSaugRadius()), Cos(angle, GetSaugRadius()), 0, 0, 150,
    RGBa(255, 100, 180, 100));
} 
RemoveObject(this());
return(1);


/* Produkteigenschaften */

public IsChemicalProduct: return(1);

/* Forschung */

public GetResearchBase: return(0);

Heal:
DoEnergy(+1,Contained());
var c = 20+Random(41);
    CreateParticle("PxSpark", Random(11)-5, Random(20)-10, 0, 0, c,
      RGBa(255, Random(100), 0, c*4, 128));
return(1);
