#strict

Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  SetComDir(COMD_Left());
  if(Random(2)) SetComDir(COMD_Right());
  SetEntrance(1);
  return(1);

RejectCollect:
  return(1);

Fighting:
  if (KannAngreifen()) return(SetAction("Punch"));
  return(1);

Power:
  return(1);
CritRate:
  return(1);
Speed:
  return(10);

WeaponSound:
  return(Sound("SwordHit*"));
DeathSound:
  return(Sound("Die"));
HurtSound:
  return(Sound("Hurt*"));

KannAngreifen:
  if(Local(1))
    return(SetLocal(1,0));
  return(Not(Random(Speed())));

Strike:
  WeaponSound();
  // Schadensberechnung
  SetVar(0,Power());
  if(SetVar(2,ObjectCall(GetActionTarget(),"Abwehr")))
    SetVar(0,Var(0)/Var(2));
  SetVar(0,ZusatzSchaden(Var(0)));
  if(Random(100)<CritRate())
    SetVar(1,1);
  if(Var(1)) {
    SetVar(0,Var(0)*2);
    Punch(GetActionTarget(),Max(Var(0),1));
  } else {
    DoEnergy(-Max(Var(0),1),GetActionTarget());
  }
  ObjectCall(GetActionTarget(),"TakeDamage",Max(Var(0),1));
  return(Max(Var(0),1));

ZusatzSchaden:
  return(Par(0));

HasShield:
  return (FindObject(SHIA,0,0,0,0,0,"Shield",Par(0)));

TakeDamage:
  SetLocal(0,Max(Par(0),1),CreateObject(__SA));
  return(1);

Damage:
  TakeDamage(Par(0));
  return(1);

CatchBlow:
//Par(0) ist die Stärke des Treffers
//Par(1) ist das schlagende Objekt [pfeil, krieger, etc.]
  if (SEqual(GetAction(),"Die")) return(0);
  if(Not(Random(2))) HurtSound();
  return(1);

Redefine:
  ChangeDef(Par(0));
  SetAction("Walk");
  return(1);

Death:
  SetAction("Die");
  DeathSound();
  GibErfahrung();
  return(1);

GibErfahrung:
  var obj; 
  while (obj=FindObject(0, -500,-200,1000,400, OCF_CrewMember(), 0,0, NoContainer(), obj)) 
    DoCrewExp(GetValue(0,GetID()),obj);
  return(1);

Search:
  if(Not(SEqual(GetAction(),"Walk")))  return(0);
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
  SetAction("SwordFight",Par(0));
  ObjectSetAction(Par(0),"Fight",this());
  // First Strike
  SetLocal(1,1);
  return(1);

Remove:
  while(Contents()) Exit(Contents());
  RemoveObject();
  return(1);
