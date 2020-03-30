#strict

Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  SetComDir(COMD_Left());
  if(Random(2)) SetComDir(COMD_Right());
  SetEntrance(1);
  if(Equal(Random(5),0)) CreateContents(GS3A);
  if(Equal(Random(5),0)) CreateContents(GS3A);
  if(Equal(Random(3),0)) CreateContents(ZF3A);
  if(Equal(Random(8),0)) CreateContents(ZF3A);
  return(1);

RejectCollect:
  return(1);

Fighting:
  return(SetAction("SwordFight",Par(0)));

SwordFighting:
  if (Not(Random(3))) return(SetAction("SwordStrike"));
  if (Not(Random(3))) return(SetAction("SwordThrust"));
  return(1);

SwordStrike:
  SwordSound();
  if (Not(Random(2))) return(1);
  SetVar(0, 2);
  if (HasShield(GetActionTarget())) SetVar(0, 1);
  Punch(GetActionTarget(),Var(0));
  return(1);

HasShield:
  return (FindObject(SHIA,0,0,0,0,0,"Shield",Par(0)));

SwordSound:
  Sound("SwordHit*");
  return(1);

FightProcess:
  if(Random(2)) return(1);
  SetAction("Punch");
  return(1);
Punching:
  if(Not(Random(3))) Sound("Kime*");
  if(Not(Random(5))) Sound("Punch*");
  if(Not(Random(2))) return(1);
  Punch(GetActionTarget());
  return(1);
CatchBlow:
  if (SEqual(GetAction(),"Dead")) return(0);
  if(Not(Random(5))) Call("Hurt");
  return(1);
Hurt:
  Sound("Hurt*");
  return(1);
Get:
  Sound("Grab");
  return(1);
Put:
  Sound("Grab");
  return(1);
Death:
  GibErfahrung();
  Sound("die_skel.wav");
  ObjectCall(CreateObject(_GTT,0,10),"Sterb","Skelett");
  RemoveObject();
  return(1);
GibErfahrung:
  var obj; 
  while (obj=FindObject(0, -500,-200,1000,400, OCF_CrewMember(), 0,0, NoContainer(), obj)) 
    DoCrewExp(GetValue(0,GetID()),obj);
  return(1);

DeepBreath:
  Sound("Breath");
  return(1);

Redefine:
  ChangeDef(Par(0));
  SetAction("Walk");
  return(1);

Search:
  if(OnFire())  if(Equal(Random(3),0)) Extinguish();
  while(SetLocal(0,FindObject(0,-400,-400,800,800,OCF_CrewMember(),0,0,NoContainer(),Local(0))))
    if(GetOwner(Local(0))!=-1) 
      return(MachDichaufdieSocken());
  return(1);

MachDichaufdieSocken:
  SetCommand(this(), "MoveTo", 0, GetX(Local(0)),GetY(Local(0))); 
  return(1);

Nahkampf:
  while(SetVar(0,FindObject(0,-16,-15,32,30,OCF_CrewMember(),0,0,NoContainer(), Var(0))))
    if(GetOwner(Var(0))!=-1) 
      return(Fight(Var(0)));
  return(1);

Fight:
  if(Not(GetAlive(Par(0)))) return(1);
  SetAction("Fight",Par(0));
  ObjectSetAction(Par(0),"Fight",this());
  return(1);
