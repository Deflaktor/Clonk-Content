#strict
#include PRNT

Check:
  SetAction("Delay");
  return(1);

GetRadius:
  return(80);
  
Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

BlowUp:
  while(Var(0)=FindObject(0,-GetRadius(),-GetRadius(),GetRadius()*2,GetRadius()*2,0,0,0,NoContainer(),Var(0))) {
    if (Distance(GetX(),GetY(),GetX(Var(0)),GetY(Var(0)))<GetRadius()) {
      if(GetOwner()!=GetOwner(Var(0))) {
        DoEnergy(-10, Var(0));
        DoDamage(10, Var(0));
        var i;
        while(!LitUp(Contents(i,Var(0)))&&i<5)
          i++;
      }
      LitUp(Var(0));
    }
  }
  for(var angle=0; angle<360; angle+=1152/GetRadius()) { 
    CreateParticle("Fire", Sin(angle, GetRadius()), Cos(angle, GetRadius()),0,0,50, RGBa(100,100,180,50));
  } 
  RemoveObject();
  return(1);
  
LitUp:
  Var(0)=Par(0);
  if((GetOCF(Var(0)) & OCF_Collectible()) != 0) {
    if(!ObjectCall(Var(0), "NoShiftOwner"))
      SetOwner(GetOwner(),Var(0));
    if(!ObjectCall(Var(0),"Hurt", Contained(Var(0)) ) && GetID(Var(0)) != ST58 && GetID(Var(0)) != S658 && GetID(Var(0)) != CHST) {
      ObjectCall(Var(0),"Activate", GetCrew(0,GetOwner()));
      ObjectCall(Var(0),"Hit");
    }
  }
  /*if(GetID(Var(0))==CHST||GetID(Var(0))==S582||GetID(Var(0))==ST58||GetID(Var(0))==S658)
    return(0);*/
  return(1);

Hit:
  SetAction("BlowUp");
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);
