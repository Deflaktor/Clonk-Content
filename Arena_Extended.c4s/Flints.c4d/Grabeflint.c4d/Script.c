#strict
#include PRNT

Check:
  Local(2)=Par(0);
  SetAction("Depart");
  return(1);

NoShiftOwner:
  return(!ActIdle());

Rotate:
  if(ActIdle())
    SetR(GetR()+10);
  return(1);

Shot:
  SetAction("Delay");
  return(1);

CheckHit:
  while(Var(0)=FindObject(0,Par(0),Par(1),Par(2),Par(3),OCF_Alive(),0,0,NoContainer(),Var(0)))
    if(GetAlive(Var(0))&&GetOwner(Var(0))!=GetOwner()&&GetID(Var(0))!=__DV)
      return(Var(0));
  while(Var(1)=FindObject(0,1,0,0,0,OCF_Alive(),0,0,NoContainer(),Var(1)))
    if(GetAlive(Var(1))&&GetOwner(Var(1))!=GetOwner()&&GetID(Var(0))!=__DV)
      return(Var(1));
  return(0);

protected Departure2:
  if(Contained()) return(SetAction("Idle"));
  Sound("Catapult");
  SetXDir(GetXDir()/Abs(GetXDir())*70);
  Var(0)=GetXDir();
  //SetXDir(SetVar(0, Mul(GetXDir(), 4)));
  SetYDir(-28);
  SetRDir(Mul(Var(), -3));
  SetLocal(0, Sub(Mul(GreaterThan(Var()), 2), 1));
  SetLocal(1, 20);
  return(1);

RejectEntrance:
  if(!ActIdle())
    return(1);
  return(0);

protected Entrance:
  SetAction("Idle");
  SetLocal();
  SetLocal(1);
  SetOwner(GetOwner(Par(0)));
  return(1);

protected Hit:
  Explode(10);
  if(Not(Random(5))) return(1);
  if(Random(3)) SetRDir(Sub(0, GetRDir()));
  if(Not(GBackSolid(0, -10))) SetYDir(-10);
  if(Not(ActIdle())) NormalFlight();
  if(GBackSolid(-10)) return(SetXDir(15));
  if(GBackSolid(10)) return(SetXDir(-15));
  SetXDir(Div(GetXDir(), 3));
  return(1);

IsSuperKampfer:
  return(FindObject(SRKR));
  
Hurt:
  if(!Par(0))
    return(1);
  
  if(GetID(Par(0))==CLON||GetID(Par(0))==CLSK||GetID(Par(0))==CLSH) {
    if(GetEnergy(Par(0))<100) {
	    Sound("Wololo");
		if(GetID(Par(0))==CLSK)
		  Var(1)=Par(0)->CreateObject(KIK1,0,10);
		else
		  Var(1)=Par(0)->CreateObject(KIL1,0,10);
		if(Var(1))
		  Var(1)->CreateObject(CTOT,0,18);
		SetOwner(GetOwner(),Var(1));
		while( Var(2)=Contents(0,Par(0)) ) {
		  Exit(Var(2));
		  Enter(Var(1), Var(2));
		}
		ObjectCall(Par(0),"Destroy");
	} else {
	  Sound("Platsch");
	  Par(0)->Damaged(100, GetOwner());
	}
  } else {
    Sound("Wololo");
    if(GetID(Par(0))==__DV)
      return(1);
    SetOwner(GetOwner(),Par(0));
    ObjectCall(Par(0),"SetMyColor");
    Par(0)->CreateObject(CTOT,0,18);
  }
  SetXDir(-GetXDir()/2);
  Sound("ProjectileHit*",0,0,100);
  SetRDir(Div(GetRDir(), 6));
  SetYDir(GetYDir() - 15);
  SetLocal(0,GetXDir());
  SetLocal(1,GetYDir());
  SetAction("BouncedOff");
  return(1);

NormalCheck:
  while(Var(0)=FindObject(GetID(Local(2)),-30,-20,60,40,OCF_Alive(),0,0,NoContainer(),Var(0)))
    if(Var(0)==Local(2)) {
      SetAction("Idle");
      return(Enter(Local(2)));
    }
  Var(0)=Angle(GetX(),GetY(),GetX(Local(2)),GetY(Local(2)));
  var speed = 30;
  SetLocal(0,BoundBy(Local(0)+Sin(Var(0),25),-speed,speed));
  SetLocal(1,BoundBy(Local(1)-Cos(Var(0),25),-speed,speed));
  SetXDir(Local(0));
  SetYDir(Local(1)-5);
  if(GetActTime()>150) NormalFlight();
  return(1);

protected FlyCheck:
  if(Var(0)=CheckHit(-18,-18,36,36)) return(Hurt(Var(0)));
  Var(0)=0;
  while(Var(0)=FindObject(GetID(Local(2)),-32,-20,64,40,OCF_Alive(),0,0,NoContainer(),Var(0)))
    if(Var(0)==Local(2)) {
      SetAction("Idle");
      return(Enter(Local(2)));
    }
  if(SetLocal(1,Local(1)-1)<1) return(NormalFlight());
  SetXDir(GetXDir()-Local(0)*10);
  if(Local(1)>16) SetYDir(GetYDir()-3);
  if(Local(1)<15) SetYDir(GetYDir()-12);
  CastObjects(_PRC,1,10);
  return(1);

ShotCheck:
  if(Var(0)=CheckHit(-18,-18,36,36)) return(Hurt(Var(0)));
  return(1);

NormalFlight:
  SetRDir(Div(GetRDir(), 6));
  SetYDir(Div(GetYDir(), 2));
  SetAction("Idle");
  SetLocal(); SetLocal(1);
  return(1);
