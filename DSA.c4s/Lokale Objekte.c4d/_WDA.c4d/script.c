Initialize:
  SetAction("Wait");
  return(1);

ActivateEntrance:
  SetLocal(0,Par(0));
  SetCommand(Par(0),"none");
  if(SEqual(GetAction(),"Ready")) Call("Auswahl1");
  return(1);

Auswahl1:
  SetAction("Wait");
  Message("Wollt ihr in die Arena?",this());
  CreateMenu(0,Local(0),this(),0,0,0,0,1);
  AddMenuItem("Ja (10S)","ArenaZahlen",YJ3A,Local(0));
  AddMenuItem("Nein","Ablehnen",YN3A,Local(0));
  AddMenuItem("Was ist die Arena?","Explain",YF3A,Local(0));
  return(1);

ArenaZahlen:
  if(GreaterThan(GetWealth(0),9)) Call("LassSieRein");
  if(LessThan(GetWealth(0),10)) Message("Ihr habt nicht genug Geld.",this());
  return(1);

Ablehnen:
  SetVar(0,Random(3));
  if(Equal(Var(0),0)) Message("Rondra sei mit euch!",this());
  if(Equal(Var(0),1)) Message("Bis zum nächsten Mal.",this());
  if(Equal(Var(0),2)) Message("Na gut, dann eben nicht.",this());
  return(1);

LassSieRein:
  Message("Hereinspaziert!");
  SetWealth(0,Sum(GetWealth(0),-10));
  ObjectCall(FindObject(FT3A,20,-100,100,100),"Open");
  SetLocal(9,1,FindObject(_AR1,200,-20,50,50));
  return(1);

Explain:
  Message("In der Arena könnt ihr gegen einige andere Lebensmüd..ähh.. Freiwillige antreten. Der Eintritt kostet 10S, Ihr könnt aber etwas gewinnen!",this()); 
  return(1);