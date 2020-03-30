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
  if(Equal(Var(0),0)) Message("Hesinde zum Gruss.",this());
  if(Equal(Var(0),1)) Message("Kann ich Euch helfen?",this());
  CreateMenu(0,Local(0),this());
  AddMenuItem("Komplette Heilung (5S)","Test1",HE3A,Local(0));
  AddMenuItem("Einige Wunden kurieren (2S)","Test2",HC3A,Local(0));
  AddMenuItem("Zauberenergie auffrischen (5S)","Test3",ZF3A,Local(0));
  AddMenuItem("Kleine Meditation (2S)","Test4",ZC3A,Local(0));
  return(1);

MoneyCheck:  //22
  if(LessThan(GetWealth(0),Par(0))) Message("So leid es mir tut, ich muss auch von etwas leben.",this());
  if(GreaterThan(GetWealth(0), Sub(Par(0),1) ))  if(SetWealth(0, Sub(GetWealth(0),Par(0)) ))  return(1);
  return(0);

Test1:
  if(Call("MoneyCheck",5)) Call("Heil",10000);
  return(1);

Test2:
  if(Call("MoneyCheck",2)) Call("Heil",100);
  return(1);

Test3:
  if(Call("MoneyCheck",5)) Call("Zaub",10000);
  return(1);

Test4:
  if(Call("MoneyCheck",2)) Call("Zaub",100);
  return(1);


Heil:
  DoEnergy(Par(0),Local(0));
  Sound("Magic1.wav");
  return(1);

Zaub:
  SetVar(0,Par(0));
  SetVar(1,0);
  while(GreaterThan(Var(0),Var(1))) if(IncVar(1)) DoMagicEnergy(1,Local(0));
  Sound("Magic1.wav");
  return(1);


