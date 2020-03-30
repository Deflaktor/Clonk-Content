Check:
  if (Not(Contained())) return(0);
  if(Local(6))
    return(0);
  while (SetVar(0,FindContents(P13A,Contained())))  Enter(this(),Var(0));
  while (SetVar(0,FindContents(P23A,Contained())))  Enter(this(),Var(0));
  while (SetVar(0,FindContents(P33A,Contained())))  Enter(this(),Var(0));
  while (SetVar(0,FindContents(P43A,Contained())))  Enter(this(),Var(0));
  while (SetVar(0,FindContents(P53A,Contained())))  Enter(this(),Var(0));
  while (SetVar(0,FindContents(P63A,Contained())))  Enter(this(),Var(0));
  while (SetVar(0,FindContents(P73A,Contained())))  Enter(this(),Var(0));
  while (SetVar(0,FindContents(P83A,Contained())))  Enter(this(),Var(0));
  return(1);

Activate:
  SetLocal(0,Par(0));
  CreateMenu(0,Par(0),this(),0,"Keine Munition vorhanden!");
  if(FindContents(P13A)) AddMenuItem("Normale Pfeile",       "Auswahl",P13A,Par(0));
  if(FindContents(P53A)) AddMenuItem("Unzerstörbare Pfeile", "Auswahl",P53A,Par(0));
  if(FindContents(P63A)) AddMenuItem("Kriegspfeile",         "Auswahl",P63A,Par(0));
  if(FindContents(P23A)) AddMenuItem("Hylaier Pfeile",       "Auswahl",P23A,Par(0));
  if(FindContents(P33A)) AddMenuItem("Giftpfeile",           "Auswahl",P33A,Par(0));
  if(FindContents(P43A)) AddMenuItem("Antimagierpfeile",     "Auswahl",P43A,Par(0));
  AddMenuItem("Munition zählen","Ueber7PfeileMusstDuSterben",KO3A,Par(0));
  if(Local(6))
    AddMenuItem("Pfeile reintun","DannHaltDoch",KO3A,Par(0));
  else
    AddMenuItem("Pfeile rausnehmen","DannHaltNicht",KO3A,Par(0));
  SetAction(GetAction());
  return(1);

Auswahl:
  SetLocal(1,Par(0));
  return(1);

Ueber7PfeileMusstDuSterben:
  SetVar(1,ContentsCount(P13A,this()));
  SetVar(2,ContentsCount(P23A,this()));
  SetVar(3,ContentsCount(P33A,this()));
  SetVar(4,ContentsCount(P43A,this()));
  SetVar(5,ContentsCount(P53A,this()));
  SetVar(6,ContentsCount(P63A,this()));
  SetVar(7,ContentsCount(P73A,this()));
  SetVar(8,ContentsCount(P83A,this()));
  Message("Normale Pfeile: %d|Hylaier Pfeile: %d|Giftpfeile: %d|Antimagierpfeile: %d|Unzerstörbare Pfeile: %d| Kriegspfeile: %d", this(),Var(1),Var(2),Var(3),Var(4),Var(5),Var(6),Var(7),Var(8));
  return(1);


Ammochange:
  SetLocal(1,0);
  if(Equal(Local(1),0)) if(FindContents(P53A)) if(SetLocal(1,P53A)) Call("ChangeDone","Elfenpfeile");
  if(Equal(Local(1),0)) if(FindContents(P13A)) if(SetLocal(1,P13A)) Call("ChangeDone","Normale Pfeile");
  if(Equal(Local(1),0)) if(FindContents(P63A)) if(SetLocal(1,P63A)) Call("ChangeDone","Kriegspfeile");
  if(Equal(Local(1),0)) if(FindContents(P33A)) if(SetLocal(1,P33A)) Call("ChangeDone","Giftpfeile");
  return(1);


ChangeDone:
  Message("Munition gewechselt: %s",this(),Par(0));
  return(1);

DannHaltNicht:
  SetLocal(6,1);
  while(Contents())  Exit(Contents());
  return(1);

DannHaltDoch:
  SetLocal(6,0);
  return(1);

