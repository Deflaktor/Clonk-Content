//Eines meiner ersten Objekte. Das sieht man dem Script auch deutlich an ;-)

Initialize:
  SetAction("Wait");
  return(1);

ControlUp:
  SetLocal(9,Par(0));
  if(SEqual(GetAction(),"Wait")) Call("Arbeite");
  return(1);

Arbeite:
  SetAction("busy");
  SetVar(0,Random(3));
  if(Equal(Var(0),0)) Message("Womit kann ich euch behilflich sein?",this());
  if(Equal(Var(0),1)) Message("Was hättet ihr denn gerne?",this());
  if(Equal(Var(0),2)) Message("Wie kann ich euch dienen?",this());
  CreateMenu(0,Local(9),this(),2);
  AddMenuItem("Rapier kaufen","Kaufen",RA3A,Local(9));
  AddMenuItem("Streitkolben kaufen","Kaufen",SK3A,Local(9));
  AddMenuItem("Schwert kaufen","Kaufen",SWOR,Local(9));
  AddMenuItem("Axt kaufen","Kaufen",AXE1,Local(9));
  AddMenuItem("Schild kaufen","Kaufen",SH3A,Local(9));
  AddMenuItem("Kampfstab kaufen","Kaufen",KP3A,Local(9));
  AddMenuItem("Magierflorett kaufen","Kaufen",MT3A,Local(9));
  return(1);

Kaufen:
  if(GetWealth(0)<GetValue(0,Par(0))) return(KeinGeld());
  SetWealth(0,GetWealth(0)-GetValue(0,Par(0)));
  Sound("uncash.wav");
  SetLocal(1,0);
  CreateContents(Par(0));
  Message("Wie Ihr wünscht.",this());
  SetAction("Erhitzen");
  return(1);
  
KeinGeld:
  Message("Wollt Ihr mich betrügen?? Ihr habt ja nicht mal genug Geld!",this());
  SetAction("Wait");
  return(1);

check:
  if(GreaterThan(Local(1),5)) Call("IchHabbeFerrtigg");
  SetLocal(1,Sum(Local(1),1));
  return(1);

IchHabbeFerrtigg:
  Exit(Contents(0),0,20);
  SetAction("Wait");
  return(1);

Leise:
  SetVar(0,Random(3));
  if (Equal(Var(0),0)) Sound("SwordHit1");
  if (Equal(Var(0),1)) Sound("SwordHit2");
  if (Equal(Var(0),2)) Sound("SwordHit3");
  return(1);

Brennen:
  if(Not(Local(3))) Smoke(14,-23,12);
  Sound("Fire");
  return(1);
