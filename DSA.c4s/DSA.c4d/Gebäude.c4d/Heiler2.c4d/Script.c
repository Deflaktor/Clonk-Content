Initialize:
  SetAction("Wait");
  return(1);

ControlUp:
  SetLocal(0,Par(0));
  if(SEqual(GetAction(),"Ready")) Call("Arbeite");
  return(1);

Arbeite:   //10
  SetAction("busy");
  SetVar(0,Random(2));
  if(Equal(Var(0),0)) Message("Der Zauber ist der Stoff aus dem die Träume sind.",this());
  if(Equal(Var(0),1)) Message("Sucht euch einen Zauber aus!",this());
  CreateMenu(0,Local(0),this());
  AddMenuItem("Schriftrolle für Eisball (30S)","Test1",_SFE,Local(0));
  AddMenuItem("Schriftrolle für Manapfeil (50S)","Test2",_SFM,Local(0));
  AddMenuItem("Schriftrolle für Gruppenheilung (80S)","Test3",_SFG,Local(0));
  AddMenuItem("Schriftrolle für Schleudern (70S)","Test4",_SFS,Local(0));
  return(1);

MoneyCheck:  //22
  if(LessThan(GetWealth(0),Par(0))) Message("So leid es mir tut, ich muss auch von etwas leben.",this());
  if(GreaterThan(GetWealth(0), Sub(Par(0),1) ))  if(SetWealth(0, Sub(GetWealth(0),Par(0)) ))  return(1);
  return(0);

Test1:
  if(Call("MoneyCheck",30)) CreateObject(_SFE);
  return(1);

Test2:
  if(Call("MoneyCheck",50)) CreateObject(_SFM);
  return(1);

Test3:
  if(Call("MoneyCheck",80)) CreateObject(_SFG);
  return(1);

Test4:
  if(Call("MoneyCheck",70)) CreateObject(_SFS);
  return(1);

