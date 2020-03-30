#strict

#include KR3A


ZusatzSchaden:
  return(Par(0)*2);

Timer:
  SetLocal(11,Local(11)+1);
  HauAlleWeg();
  return(1);

HauAlleWeg:
  if(SEqual(GetAction(),"Walk"))
    if(SetVar(0,FindObject(0,-16,-15,32,30,OCF_Alive(),0,0,NoContainer(), Var(0))))
      if(GetOwner(Var(0))==-1&&SEqual(GetAction(Var(0)),"Walk")) 
        HauWeg(Var(0));
  if(SEqual(GetAction(),"Magierflorett")) MagierflorettHit();
  if(SEqual(GetAction(),"Zauberstab")) ZauberstabHit();
  if(SEqual(GetAction(),"ExcaliburFight")) ExcaliburHit();
  if(SEqual(GetAction(),"SwordFight")) SwordHit();
  if(SEqual(GetAction(),"StreitkolbenFight")) StreitkolbenHit();
  if(SEqual(GetAction(),"AxeFight")) AxeHit();
  if(SEqual(GetAction(),"RapierFight")) RapierHit();
  if(SEqual(GetAction(),"KampfstabFight")) KampfstabHit();
  if(SEqual(GetAction(),"DolchFight")) DolchHit();
  if(SEqual(GetAction(),"Fight")) SetAction("Punch");
  return(1);

HauWeg:
  SetAction("Fight",Par(0));
  ObjectSetAction(Par(0),"Fight",this());
  Fighting();
  SetLocal(11,0);
  SetLocal(10,0);
  return(1);

Strike:
  SetVar(1,_inherited());
  while(SetVar(0,FindObject(0,-24,-15,48,30,OCF_Alive(),0,0,NoContainer(), Var(0))))
    if(Random(4)) {
      Fling(Var(0),-5+10*Random(2), -4);
      if(Random(3))
        DoEnergy(-Var(1),Var(0));
    }
  return(Var(1));
