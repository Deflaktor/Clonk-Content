//Local(1) wird vom Schalter geändert. 0=Off 1=On
//Local(2) ist dann 1, wenn das Tor unter keinen Umständen aufgehen darf


Initialize:
  SetAction("Gate");
  return(1);

CheckRange:
  AssignVar(0, GetY(GetActionTarget()) );
  if (LessThan( GetY(), Sum(Var(0),-2) ))
    SetComDir(COMD_Down());
  if (GreaterThan( GetY(), Sum(Var(0),+20) ))
    SetComDir(COMD_Up());
  return(1);


Close:
  if (GreaterThan( GetY(), Sum(GetY(GetActionTarget()),+20) )) return (0);
  SetComDir(COMD_Down());
  return(1);

Open:
  Sound("Click");
  Sound("SteelGate1");
  if (LessThan( GetY(), Sum(GetY(GetActionTarget()),-2) )) return (0);
  SetComDir(COMD_Up());
  return(1);

Completion:
  SetComDir( COMD_Down() );
  return(1);

IstDaWer:
  if(Not(FindObject(0,-100,-50,150,100,OCF_Prey())))   Call("Close");
  if(Equal(Local(0),0))  if(Equal(Local(9),0))  if(FindObject(0,0,-20,50,60,OCF_Prey()))   Call("Open");
  if(Equal(Local(1),1))  if(Equal(Local(9),0))  if(FindObject(0,-50,-20,100,60,OCF_Prey()))   Call("Open");
  return(1);


