Hit:
  Sound("RockHit");
  return(1);

Activate:
  Sound("RadioStatic");
  SetVar(0,Local(0,Par(0)));
  CreateMenu(_RDO,Par(0),this());
  if(Var(0))
    AddMenuItem("%s","MenuDroneCfg",MI_D,Par(0),0,Par(0));
  AddMenuItem("%s","MenuReinforcements",MI_R,Par(0),0,Par(0));
  return(1);

MenuReinforcements:
  if(LessThan(GetScore(GetOwner()),GameCall("MinReinforcementsScore")))
    return(Message("Noch nicht freigegeben",this()));
  if(GreaterThan(GetCrewCount(GetOwner()),1))
    return(Message("Verstärkung bereits eingetroffen",this()));
  MakeCrewMember(DoEnergy(+100,CreateObject(SHZC,0,-3800),GetOwner()));
  Message("Verstärkung kommt",this());
  return(1);

MenuDroneCfg:
  SetVar(0,Local(0,Par(1)));
  CreateMenu(MI_D,Par(1),this());
  if(Local(1,Var(0)))
    AddMenuItem("%s","MenuDroneCfgFollow",MI_F,Par(1),0,Par(1));
  if(Not(Local(1,Var(0))))
    AddMenuItem("%s","MenuDroneCfgDFollow",MIDF,Par(1),0,Par(1));
  if(Local(2,Var(0)))
    AddMenuItem("%s","MenuDroneCfgSupply",MI_S,Par(1),0,Par(1));
  if(Not(Local(2,Var(0))))
    AddMenuItem("%s","MenuDroneCfgDSupply",MIDS,Par(1),0,Par(1));
  if(Local(3,Var(0)))
    AddMenuItem("%s","MenuDroneCfgAttack",MI_A,Par(1),0,Par(1));
  if(Not(Local(3,Var(0))))
    AddMenuItem("%s","MenuDroneCfgDAttack",MIDA,Par(1),0,Par(1));
  return(1);

MenuDroneCfgFollow:
  SetVar(0,Local(0,Par(1)));
  SetLocal(1,0,Var(0));
  MenuDroneCfg(0,Par(1));
  Sound("Off");
  return(1);
MenuDroneCfgSupply:
  SetVar(0,Local(0,Par(1)));
  SetLocal(2,0,Var(0));
  MenuDroneCfg(0,Par(1));
  Sound("Off");
  return(1);
MenuDroneCfgAttack:
  SetVar(0,Local(0,Par(1)));
  SetLocal(3,0,Var(0));
  MenuDroneCfg(0,Par(1));
  Sound("Off");
  return(1);
MenuDroneCfgDFollow:
  SetVar(0,Local(0,Par(1)));
  SetLocal(1,1,Var(0));
  MenuDroneCfg(0,Par(1));
  Sound("On");
  return(1);
MenuDroneCfgDSupply:
  SetVar(0,Local(0,Par(1)));
  SetLocal(2,1,Var(0));
  MenuDroneCfg(0,Par(1));
  Sound("On");
  return(1);
MenuDroneCfgDAttack:
  SetVar(0,Local(0,Par(1)));
  SetLocal(3,1,Var(0));
  MenuDroneCfg(0,Par(1));
  Sound("On");
  return(1);

SelfDestruct:
  SetAction("SelfDestruct");
  return(1);

Destruct:
  RemoveObject();
  return(1);