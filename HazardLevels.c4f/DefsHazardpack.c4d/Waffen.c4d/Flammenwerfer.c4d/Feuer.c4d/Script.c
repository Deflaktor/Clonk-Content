#strict
#include _POV

local abgefeuert;

Launch:  
  if(Equal(Par(0),DIR_Left()))  SetLocal(0,-50);
  if(Equal(Par(0),DIR_Right())) SetLocal(0,50);
  if(Par(2))
    Local(0)=0;

  
  SetLocal(1,Sum(Local(0),Random(10)));
  SetLocal(2,Sub(GetY(),Sub(2,Random(2))));
  SetLocal(4,20);
  Incinerate();
  abgefeuert = 1;
  return(SetAction("Fliegen"));
  
Check:
if(GetAction()S="Idle"&&abgefeuert)
RemoveObject();
return(1);

Fliegen:
  SetXDir(Local(1));
  
  if(Random(2))      SetYDir(Mul(1,Random(10)));
  if(Not(Random(2))) SetYDir(Mul(-1,Random(10)));

  if(GreaterThan(GetActTime(),Local(4))) RemoveObject();
  
  if(SetVar(0,FindObject(ZAP1,-20,-20,40,40)))                          return(Zap(Var(0)));
  // Kiste
  if(SetVar(0,FindObject(_CR2,-5,-5,10,10,0,0,0,NoContainer())))        return(Benzin(Var(0)));
  // Explosive Kiste
  if(SetVar(0,FindObject(_ECR,-5,-5,10,10,0,0,0,NoContainer())))        return(Benzin(Var(0)));
  // Benzinkanister
  if(SetVar(0,FindObject(_AP3,-5,-5,10,10,0,0,0,NoContainer())))        if(!Random(3)) return(Incinerate(Var(0)));
  // Schleim
  if(SetVar(0,FindObject(SH10,-10,-10,20,20,0,0,0,NoContainer())))      return(ObjectCall(Var(0)),"Dangerous");
  // Eisklumpen
  if(SetVar(0,FindObject(ICE1,-10,-10,20,20,0,0,0,NoContainer())))      return(Eisklumpen(Var(0)));
  // Kokon
  if(SetVar(0,FindObject(SK5B,-10,-10,20,20,0,0,0,NoContainer())))      return(RemoveObject(Var(0)));
  // Eisstrahlen werden geschmolzen
  if(SetVar(0,FindObject(_EGM,-6,-2*GetCon()/100,12,4*GetCon()/100,0,0,0,NoContainer())))        return(RemoveObject(Var(0)));
  // Lebewesen
  if(Var(0)=CheckHit(-6,-2*GetCon()/100,12,4*GetCon()/100))		return(Lebewesen(Var(0)));
  // Leiche
  if(SetVar(0,FindObject(_GTT,-5,-5,10,10,0,0,0,NoContainer()))) return(Lebewesen(Var(0)));

  if(Stuck()) SetPosition(Sub(GetX(),Div(GetXDir(),Abs(GetXDir()))),GetY());
  
  if(Random(2)) return(DoCon(SetLocal(3,Mul(10,Random(10)))));
  if(Random(3)) return(DoCon(SetLocal(3,Mul(5,Random(10)))));
  if(Random(4)) return(DoCon(SetLocal(3,Mul(1,Random(10)))));

  return(DoCon(SetLocal(3,Mul(5,Random(10)))));
  
ContactLeft: 
  return(SetYDir(BoundBy(Mul(GetYDir(),Random(10)),-50,50)));

ContactRight:
  return(SetYDir(BoundBy(Mul(GetYDir(),Random(10)),-50,50)));  

ContactTop:
  DoCon(Mul(-1,Local(3)));
  SetLocal(2);
  return(SetYDir(50));
  
ContactBottom:
  return(SetYDir(-50));

Schmelzen:  
  if(Equal(Local(0),50)) SetVar(0,1);
  DigFree(Sum(Div(Local(0),50),Sum(GetX(),Var(0))),Local(2),12);
  CastPXS("Water",10,0,0,0);
  return(RemoveObject());

Zap:
  return(RemoveObject(Par(0)));

Benzin:
  DoDamage(Dmg(),Par(0));
  return(RemoveObject());

Eisklumpen:
  RemoveObject(Par(0));
  CastPXS("Water",5,0,0,0);
  return(RemoveObject());

Lebewesen:
  if(GetAlive(Par(0)))
    SetXDir(Sum(GetXDir(Par(0)),Div(Local(0),4)),Par(0));
  Incinerate(Par(0));
  DoEnergy(-Dmg(),Par(0));
  if(GetAlive(Par(0)))
    RemoveObject();
  return(1);

Dmg:
  return(1);
  
Wasser:
  return(RemoveObject());