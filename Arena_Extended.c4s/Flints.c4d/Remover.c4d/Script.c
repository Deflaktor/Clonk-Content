/*-- Neues Objekt --*/

#strict
#include PRNT

Initialize:
  if(FindObject(SRKR)) {
    ChangeDef(GameCall("Zufallsflint2"));
    return(ObjectCall(this(),"Initialize"));
  }
  return(1);

NeededId:
  return(_MFF);
  
Entrance:
  SetOwner(GetOwner(Par(0)),this());
  return(1);

Activate:
  // Beim Träger nach Ammo suchen
  if(Not(SetVar(0,FindObject(NeededId(),-1,-1,2,2,0,0,0,Contained(),0))))
    return(MessageError());
  if(Var(0)==this())
    return(MessageError());
  // Ammo nehmen
  Sound("Connect");
  RemoveObject(Var(0));
  ChangeDef(GetNeueID());
  this()->Redefine();
  //ObjectCall(this(),"Redefine");
  return(1);
  
  

MessageError:
  Sound("NoAmmo");
  Message(Format("Es fehlt noch ein %s", GetName(0, NeededId())), this());
  return(1);

Redefine:
  if(Contained())
    while(ScrollContents(Contained())!=this()) {}
  return(1);

GetNeueID:
  return(_MF2);

GetSaugRadius:
  return(144);

GetMoney:
  return(0);

IstEinRemover:
  return(1);

Hit:
SetLocal(0,0);
while(SetVar(1,FindObject(0,-GetSaugRadius(),-GetSaugRadius(),GetSaugRadius()*2,GetSaugRadius()*2,0,0,0,NoContainer(),Var(1))))
{
  if(!(GetOwner()==GetOwner(Var(1))&&GetOCF(Var(1)) & OCF_CrewMember()))
  {
    if (!( GetCategory(Var(1)) & C4D_StaticBack() ))
    {
      if (Distance(GetX(),GetY(),GetX(Var(1)),GetY(Var(1)))<GetSaugRadius()) 
      {
        if(!ObjectCall(Var(1),"IstEinRemover"))
        {
          if(!ObjectCall(Var(1),"Destroy",GetOwner())) {
            SetWealth(GetOwner(),GetWealth(GetOwner())+GetMoney());
            CreateParticle("PSpark",-GetX()+GetX(Var(1)),-GetY()+GetY(Var(1)),0,0,150,RGBa(100,100,180,100));
            RemoveObject(Var(1));
          }
        } else {
          SetOwner(GetOwner(),Var(1));
          ObjectSetAction(Var(1),"Timer");
        }
      }
    }
  }
}
Sound("Saug");
for(var angle=0; angle<360; angle+=1152/GetSaugRadius())
{ 
  CreateParticle("PSpark", Sin(angle, GetSaugRadius()), Cos(angle, GetSaugRadius()),0,0,50, RGBa(100,100,180,50));
} 
RemoveObject(this());
return(1);