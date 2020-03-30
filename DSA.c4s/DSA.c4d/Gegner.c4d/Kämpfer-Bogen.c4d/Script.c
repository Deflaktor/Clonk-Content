#strict

#include _GTE

Initialize:
  _inherited();
  SetLocal(0,0);
  SetLocal(1,3);
  if(Equal(Random(8),0)) CreateContents(GD3A);
  if(Equal(Random(8),0)) CreateContents(GD3A);
  if(Equal(Random(8),0)) CreateContents(GS3A);
  if(Equal(Random(8),0)) CreateContents(GS3A);
  if(Equal(Random(8),0)) CreateContents(GS3A);
  if(Equal(Random(8),0)) CreateContents(GS3A);
  if(Equal(Random(8),0)) CreateContents(GS3A);
  if(Equal(Random(8),0)) CreateContents(GS3A);
  if(Equal(Random(8),0)) CreateContents(GS3A);
  if(Equal(Random(8),0)) CreateContents(GS3A);
  return(1);

Power:
  return(1);
CritRate:
  return(1);
Speed:
  return(10);

WeaponSound:
  if(Random(2)) 
    Sound("Kime*");
  else 
    Sound("Punch*");
  return(1);
DeathSound:
  return(Sound("Die"));
HurtSound:
  return(Sound("Hurt*"));

Fighting:
  if (KannAngreifen()) return(SetAction("Strike"));
  return(1);
 
Death:
  _inherited();
  ObjectCall(CreateObject(KT3A,0,10),"Sterb","Bogen");
  RemoveObject();
  return(1);

Search:
  return(1);

FindGegner:
  if(OnFire()) if(Equal(Random(3),0)) Extinguish();
  if(Not(SEqual(GetAction(),"Walk"))) return(0);
  while(SetLocal(0,FindObject(0,1,-80,400,200,OCF_CrewMember(),0,0,NoContainer(),Local(0))))
    if(GetOwner(Local(0))!=-1) 
      return(ShootRight());

  while(SetLocal(0,FindObject(0,-400,-80,400,200,OCF_CrewMember(),0,0,NoContainer(),Local(0))))
    if(GetOwner(Local(0))!=-1) 
      return(ShootLeft());
  SetXDir(0);
  return(1);

//Local(8) wird vom Pfeil übermittelt

ShootRight:
  SetDir(DIR_Right());
  if(SEqual(GetAction(),"Reload")) return(0);
  Call("TargetAquire");
  return(1);

ShootLeft:
  SetDir(DIR_Left());
  if(SEqual(GetAction(),"Reload")) return(0);
  Call("TargetAquire");
  return(1);

TargetAquire:
//Var(0) ist X-Koordinate des Gegners relativ zum Einschlag des Pfeils, Var(1) die Y-Koordinate
  SetVar(0,Sub(Local(8),GetX(Local(0))));
  SetVar(1,Sub(Local(9),GetY(Local(0))));
  if(GreaterThan(Abs(Var(1)),Abs(Var(0))))   Call("YAim",Var(1));
  if(Not(GreaterThan(Abs(Var(1)),Abs(Var(0)))))  Call("XAim",Var(0),Par(0));
  return(1);

XAim:
  SetAction("AimBow");
  if(GreaterThan(Par(0),10))  SetVar(7,1);
  //if(GreaterThan(Par(0),55))  SetVar(7,2);
  if(LessThan(Par(0),-10))    SetVar(7,-1);
  //if(LessThan(Par(0),-55))    SetVar(7,-2);

  if(Equal(GetDir(),DIR_Left()))  SetVar(7,Mul(Var(7),-1));

  SetLocal(1,Sum(Local(1),Var(7)));
  if(LessThan(Local(1),2)) SetLocal(1,2);
  if(GreaterThan(Local(1),4)) SetLocal(1,5);
  return(1);

YAim:
  SetAction("AimBow");
  if(GreaterThan(Par(0),-10))  SetVar(7,-1);
  //if(GreaterThan(Par(0),-55))  SetVar(7,-2);
  if(LessThan(Par(0),10))    SetVar(7,1);
  //if(LessThan(Par(0),55))    SetVar(7,2);

  SetLocal(1,Sum(Local(1),Var(7)));
  if(LessThan(Local(1),2)) SetLocal(1,2);
  if(GreaterThan(Local(1),4)) SetLocal(1,5);
  return(1);


SimulierWerfen:
  if(Not(FindContents(XA3A))) CreateContents(XA3A);
  SetLocal(5,FindContents(XA3A));
  SetLocal(1,this(),Local(5));
  if(Equal(GetDir(),DIR_Left()))   Call("LinksFire");
  if(Equal(GetDir(),DIR_Right()))   Call("RechtsFire");
    return(1);

/*-----Local(1) war früher Phase, ist aber Umstrukturierungen
            in der Actmap zum Opfer gefallen ----*/

RechtsFire:
  if(Equal(Local(1),2))   Exit(Local(5),4,-10,52,8,-3,3);
  if(Equal(Local(1),3))   Exit(Local(5),6,-10,78,11,0,3);
  if(Equal(Local(1),4))   Exit(Local(5),8,-10,104,14,3,3);
  if(Equal(Local(1),5))   Exit(Local(5),10,-10,130,17,6,3);
  Sound("Bow");
  SetAction("Reload");
  return(1);

LinksFire:
  if(Equal(Local(1),2))   Exit(Local(5),-4,-10,-52,-8,-3,-3);
  if(Equal(Local(1),3))   Exit(Local(5),-6,-10,-78,-11,0,-3);
  if(Equal(Local(1),4))   Exit(Local(5),-8,-10,-104,-14,3,-3);
  if(Equal(Local(1),5))   Exit(Local(5),-10,-10,-130,-17,6,-3);
  Sound("Bow");
  SetAction("Reload");
  return(1);


BinIchRedwolfWuerdig:
  if(GreaterThan(GetActTime(this()),59)) SetAction("Walk");
  return(1);
