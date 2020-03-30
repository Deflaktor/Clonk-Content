//Local(1) wird vom Schalter geändert. 0=Off 1=On
//Local(2) ist dann 1, wenn das Tor unter keinen Umständen aufgehen darf


Initialize:
  SetBlackGate();
  return(1);

SetBlackGate:
  SetAction("GateBlack");
  SetLocal(0,0);
  if(SEqual(GetAction(FindObject(SC3B)),"Black"))
    Open();
  else
    Close();
  return(1);

SetWhiteGate:
  SetAction("GateWhite");
  SetLocal(0,1);
  if(SEqual(GetAction(FindObject(SC3B)),"White"))
    Open();
  else
    Close();
  return(1);

SwitchIsWhite:
  if(Local(0))
    Open();
  else
    Close();
  return(1);

SwitchIsBlack:
  if(!Local(0))
    Open();
  else
    Close();
  return(1);

Close:
  if (GreaterThan( GetY(), Sum(GetY(GetActionTarget()),+20) )) return (0);
  SetComDir(COMD_Down());
  return(1);

Open:
  if (LessThan( GetY(), Sum(GetY(GetActionTarget()),-2) )) return (0);
  SetComDir(COMD_Up());
  return(1);

