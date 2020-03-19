/* --- Bummerang --- */
#strict
#include _POV

Dmg: return(30);

protected Departure:
  if(Not(GetXDir())) return(1);
  if(Not(BitAnd(GetOCF(Par()), OCF_Living()))) return(1);
  Local(2)=Par(0);
  SetAction("Depart");
  return(1);

protected Departure2:
  if(Contained()) return(SetAction("Idle"));
  Sound("Catapult");
  SetXDir(SetVar(0, Mul(GetXDir(), 4)));
  SetYDir(-30);
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
  Sound("BmHit");
  if(Not(Random(5))) return(1);
  if(Random(3)) SetRDir(Sub(0, GetRDir()));
  if(Not(GBackSolid(0, -10))) SetYDir(-10);
  if(Not(ActIdle())) NormalFlight();
  if(GBackSolid(-10)) return(SetXDir(15));
  if(GBackSolid(10)) return(SetXDir(-15));
  SetXDir(Div(GetXDir(), 3));
  return(1);

Hurt:
  Var(0)=Dmg();
  //Var(0)=35;
  //Var(0)=GetMass(Par(0))*2*Abs(GetXDir())/200;
  DoEnergy(-Var(0),Par(0));
  DoDamage(Var(0),Par(0));
  Fling(Par(0),GetXDir()/25,GetYDir()/25);
  SetXDir(-GetXDir()/2);
  Sound("ProjectileHit*",0,0,100);
  SetRDir(Div(GetRDir(), 6));
  SetYDir(GetYDir() - 15);
  //SetYDir(Div(GetYDir(), 2));
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
  return(1);

protected FlyCheck:
  if(Var(0)=CheckHit(-16,-16,32,32)) return(Hurt(Var(0)));
  Var(0)=0;
  while(Var(0)=FindObject(GetID(Local(2)),-30,-20,60,40,OCF_Alive(),0,0,NoContainer(),Var(0)))
    if(Var(0)==Local(2)) {
      SetAction("Idle");
      return(Enter(Local(2)));
    }
  if(SetLocal(1,Local(1)-1)<4) return(NormalFlight());
  SetXDir(GetXDir()-Local(0)*10);
  if(Local(1)>16) SetYDir(GetYDir()-4);
  if(Local(1)<15) SetYDir(GetYDir()-12);
  return(1);

NormalFlight:
  SetRDir(Div(GetRDir(), 6));
  SetYDir(Div(GetYDir(), 2));
  SetAction("Idle");
  SetLocal(); SetLocal(1);
  return(1);

IsThrowWeapon:
  return(1);

public MaxRange:
  return(75);