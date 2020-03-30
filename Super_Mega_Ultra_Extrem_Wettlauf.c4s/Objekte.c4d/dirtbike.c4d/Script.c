//Local(0) == Nitro Speed
//Local(1) == Nitro Time

Redefine:
SetVar(0,GetAction());
SetVar(1,GetYDir());
SetVar(2,GetXDir());
SetVar(3,GetRDir());
ChangeDef(Par(0));
SetAction(Var());
SetYDir(Var(1));
SetXDir(Var(2));
SetRDir(Var(3));
return(1);

Completion:
  if(Not(Local(1)))
  SetR();
  SetAction("Act1");
  return(SetDir(DIR_Left()));
ContainedUp:
  if(GameCall("DontMove")) return(1);
  if(Not(Local(1)))
  SetR();
  if(Not(SEqual(GetAction(),"Act1"))) return(1);
  return(SetAction("Act2"));
ContainedLeft:
  if(GameCall("DontMove")) return(1);
  if(Not(Local(1)))
  SetR();
  SetDir(DIR_Left());
  if(Stuck()) SetPosition(GetX(),GetY()-1);
  if(Not(SEqual(GetAction(),"Act2"))) return(1);
  return(SetAction("Act3"));
ContainedRight:
  if(GameCall("DontMove")) return(1);
  if(Not(Local(1)))
  SetR();
  SetDir(DIR_Right());
  if(Stuck()) SetPosition(GetX(),GetY()-1);
  if(Not(SEqual(GetAction(),"Act2"))) return(1);
  return(SetAction("Act3"));
ContainedDown:
  if(GameCall("DontMove")) return(1);
  if(Not(Local(1)))
  SetR();
  AssignVar(0,0);
  if(Equal(GetDir(),DIR_Left())) AssignVar(0,0);
  SetXDir(Var(0));
  if(SEqual(GetAction(),"Act2")) return(1);
  if(SEqual(GetAction(),"Act3")) SetAction("Act2");
  return(1);
GetOffBike:
  SetAction("Act1");
  return(1);
Exhaust:
  if(Not(Local(1)))
  SetR();
  AssignVar(0,-18);
  if(Equal(GetDir(),DIR_Left())) AssignVar(0,+18);
  return(1);
Fahren:
  if(Not(Local(1)))
  SetR();
  if(Local(1))
  SetLocal(1,Local(1)-1);
  if(Not(Local(1)))
  SetLocal();
  AssignVar(0,+60+Local());
  if(Equal(GetDir(),DIR_Left())) AssignVar(0,-60-Local());
  SetXDir(Var(0));
  AssignVar(1,-15);
  if(Equal(GetDir(),DIR_Left())) AssignVar(1,+15);
  return(1);
Damage:
  if(Not(GreaterThan(GetDamage(),40))) return(1);
  if(Not(GreaterThan(GetDamage(),80))) return(1);
  Exit(AssignVar(0,CreateContents(METL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(METL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(METL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(METL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(METL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(OBRL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(OBRL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(OBRL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(OBRL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(OBRL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(OBRL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(OBRL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(OBRL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(OBRL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(OBRL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(OBRL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  CastObjects(DFLM,20,20);
  Explode(40);
  return(1);

Destruction:
  SetVar(0,FindContents(CLNK));
  Exit(Var());
  return(1);

Verschwinde:
  SetVar(0,FindContents(CLNK));
  Exit(Var());
  ObjectCall(FindObject(CLNK,-10,-10,20,20),"Verschwinde");
  return(RemoveObject());

Destroy:
  CastObjects(_DF1,20,50,0,-20);
  SetVar(0,FindContents(CLNK));
  Exit(Var());
  ObjectCall(FindObject(CLNK,-10,-10,20,20),"Destroy");
  return(RemoveObject());

RejectCollect:
  return(0);