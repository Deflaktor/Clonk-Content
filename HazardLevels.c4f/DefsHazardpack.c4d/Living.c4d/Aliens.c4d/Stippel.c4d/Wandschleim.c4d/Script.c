#strict

Initialize:
  return(SetOwner(-1));

Activity:
  if(Or(InLiquid(),Not(Local(0)))) 
    if(Not(Random(5))) 
      if(Not(GetAction() eq "Kaputt")) 
        return(SetAction("Kaputt"));
  //if(GBackSemiSolid())                   -rausgenommen, da ein Fahrstuhl sonst eine zerstörerische Wirkung hätte
  //  if(Not(GetAction() eq "Kaputt"))
  //    return(SetAction("Kaputt"));
  if(Or(InLiquid(),Not(Local(0)))) return(0);
  if(GBackSemiSolid()) return(0);

  if(GetCon()<100) DrawMaterialQuad("Slime-Metal1",GetX()-((8*GetCon())/100),GetY()-((8*GetCon())/100),GetX()+((8*GetCon())/100),GetY()-((8*GetCon())/100),GetX()+((8*GetCon())/100),GetY()+((8*GetCon())/100),GetX()-((8*GetCon())/100),GetY()+((8*GetCon())/100));
  
  if(Not(Random(Global(5)*Sqrt(ObjectCount(ST5B)+1))))                 Stippel();
  
  if(ObjectCount(WS5B)<Global(4))
    if(Equal(GetCon(),100))            return(Auswahl());
  
  return(DoCon(2));
  
Auswahl:  
  if(Not(Random(10))) Anbau(-13,-6);
  if(Not(Random(10))) Anbau(0,-6);
  if(Not(Random(10))) Anbau(13,-6);
  if(Not(Random(10))) Anbau(13,8);
  if(Not(Random(10))) Anbau(-13,8);
  if(Not(Random(10))) Anbau(13,22);
  if(Not(Random(10))) Anbau(0,22);
  if(Not(Random(10))) Anbau(-13,22);
  return(0);
  
Anbau:  
  if(Not(Inside(Sum(GetX(),Par(0)),10,Sub(LandscapeWidth(),10)))) return(0);
  if(LessThan(Sum(GetY(),Par(1)),10))                             return(0);
  if(GBackSemiSolid(Par(0)-6,Par(1)-12))                          return(0);
  if(GBackSemiSolid(Par(0),Par(1)-12))                            return(0);
  if(GBackSemiSolid(Par(0)+6,Par(1)-12))                          return(0);
  if(GBackSemiSolid(Par(0)+6,Par(1)-6))                           return(0);
  if(GBackSemiSolid(Par(0)+6,Par(1)))                             return(0);
  if(GBackSemiSolid(Par(0),Par(1)))                               return(0);
  if(GBackSemiSolid(Par(0)-6,Par(1)))                             return(0);
  if(GBackSemiSolid(Par(0)-6,Par(1)-6))                           return(0);
  if(Not(PathFree(GetX(),GetY(),GetX()+Par(0),GetY()+Par(1))))    return(0);
  if(FindObject(WS5B,Sub(Par(0),3),Sub(Par(1),8),6,15))           return(0);

  SetVar(0,CreateConstruction(WS5B,Par(0),Par(1),-1,1));
  SetLocal(0,Local(0),Var(0));

  return(1);



Incineration:
  return(SetAction("Kaputt"));



Remove:
  DrawMaterialQuad("Tunnel-Smooth",GetX()-((8*GetCon())/100),GetY()-((8*GetCon())/100),GetX()+((8*GetCon())/100),GetY()-((8*GetCon())/100),GetX()+((8*GetCon())/100),GetY()+((8*GetCon())/100),GetX()-((8*GetCon())/100),GetY()+((8*GetCon())/100));
  return(RemoveObject());





Stippel:
  ObjectCall(CreateObject(ST5B),"Frisch");
  Sound("KGGeburt");
  return(1);




