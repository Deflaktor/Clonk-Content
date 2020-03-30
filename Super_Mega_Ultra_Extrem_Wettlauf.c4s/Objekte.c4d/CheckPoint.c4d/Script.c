#strict

Initialize:
  SetAction("Los");
  Local(0)=65535;
  Local(1)=65535;
  SetVisibility(VIS_Local() | VIS_God());
  return(1);

Test:
  while(Var(0)=FindObject(CLNK,-40,-30,80,60,0,0,0,NoContainer())) return(Erstellen(Var(0)));
  while(Var(0)=FindObject(PM7K,-40,-40,80,70,0,0,0,NoContainer())) return(Erstellen(Var(0)));
  while(Var(0)=FindObject(PN7K,-40,-40,80,70,0,0,0,NoContainer())) return(Erstellen(Var(0)));
  while(Var(0)=FindObject(BIK1,-40,-40,80,70,0,0,0,NoContainer())) return(Erstellen(Var(0)));
  return(1);

Erstellen:
  var plr = GetOwner(Par(0));

  if(Local(2+plr)==1)
    return(0);
  
  SetLocal(2+plr,1);
  SetGlobal(plr*2+2,GetX());
  if(GetAction() eq "Goal")
    SetGlobal(plr*2+3,GetY()-20);
  else
    SetGlobal(plr*2+3,GetY());

  MachUnsichtbar(plr);

  if(GetAction() eq "Goal") {
    Sound("Cash", 0, 0, 0, plr+1);
    RemoveObject();
    var gc = FindObject(_GCR);
    ObjectCall(gc, "GibPunkt", plr);
    GameCall("NeueRunde", GetX(), GetY()-20);
  } else {
    Sound("Ding", 0, 0, 0, plr+1);
  }

  return(1);

MachUnsichtbar:
  Local(Par(0)/32)=Local(Par(0)/32)&(~(1<<(Par(0)%32)));
  return(Par(0));
