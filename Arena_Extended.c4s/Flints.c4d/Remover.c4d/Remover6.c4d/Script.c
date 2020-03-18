/*-- Neues Objekt --*/

#strict
#include PRNT

Initialize:
  if(FindObject(SRKR)) {
    ChangeDef(GameCall("Zufallsflint2"));
    return(ObjectCall(this(),"Initialize"));
  }
  return(1);
  
  

Entrance:
  SetOwner(GetOwner(Par(0)),this());
  return(1);


Redefine:
  if(Contained())
    while(ScrollContents(Contained())!=this()) {}
  return(1);

GetMoney:
  return(0);

IstEinRemover:
  return(1);

Hit:
SetLocal(0,0);
while(SetVar(1,FindObject(0,0,0,0,0,0,0,0,NoContainer(),Var(1))))
{
  if(!(GetOwner()==GetOwner(Var(1))&&GetOCF(Var(1)) & OCF_CrewMember()))
  {
    if (!( GetCategory(Var(1)) & C4D_StaticBack() ))
    {
        if(!ObjectCall(Var(1),"IstEinRemover"))
        {
          if(!ObjectCall(Var(1),"Destroy",GetOwner())) {
            SetWealth(GetOwner(),GetWealth(GetOwner())+GetMoney());
            CreateParticle("MSpark2",-GetX()+GetX(Var(1)),-GetY()+GetY(Var(1)),0,0,150,RGBa(100,100,180,100));
            RemoveObject(Var(1));
          }
        } else {
          SetOwner(GetOwner(),Var(1));
          ObjectSetAction(Var(1),"Timer");
        }
    }
  }
}
Sound("Saug");
RemoveObject(this());
return(1);