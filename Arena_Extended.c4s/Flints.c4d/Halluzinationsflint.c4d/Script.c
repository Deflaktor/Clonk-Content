#strict
#include PRNT

Hit:
  if(!Random(35)) {
    Var(0)=Random(5);
    //Var(0)=2;
    if(Var(0)==0)
      CastObjectsX(ST58,20,80,0,0,270,45, "Sett");
    else if(Var(0)==1)
      CastObjectsX(GetID(),20,80,0,0,270,45, "Sett");
    else if(Var(0)==2)
      CastObjectsX(QTAF,20,80,0,0,270,45, "Sett");
    else if(Var(0)==3&&!Random(2))
      CastObjectsX(HALA,20,80,0,0,270,45, "Sett");
    else
      CastObjectsX(GameCall("Zufallsflint"),20,80,0,0,270,45, "Sett");
      
    return(Explode(Sum(Random(Sum(Random(Sum(Random(Sum(Random(10),5)),5)),5)),10)));
  }
  Smoke(0,0,Sum(Random(4),6));
  Exit(Create(HAL0),0,0,Random(360), Sum(Random(10),-5), Sum(Random(3),-8), +10);
  Exit(Create(HAL1),0,0,Random(360), Sum(Random(10),-5), Sum(Random(3),-8), +10);
  Exit(Create(HAL2),0,0,Random(360), Sum(Random(10),-5), Sum(Random(3),-8), +10);
  Exit(Create(HAL3),0,0,Random(360), Sum(Random(10),-5), Sum(Random(3),-8), +10);
  Exit(Create(HAL4),0,0,Random(360), Sum(Random(10),-5), Sum(Random(3),-8), +10);
  Exit(Create(HAL5),0,0,Random(360), Sum(Random(10),-5), Sum(Random(3),-8), +10);
  Exit(Create(HAL6),0,0,Random(360), Sum(Random(10),-5), Sum(Random(3),-8), +10);
  Exit(Create(HAL7),0,0,Random(360), Sum(Random(10),-5), Sum(Random(3),-8), +10);
  Exit(Create(HAL8),0,0,Random(360), Sum(Random(10),-5), Sum(Random(3),-8), +10);
  Exit(Create(HAL9),0,0,Random(360), Sum(Random(10),-5), Sum(Random(3),-8), +10);
  SetVar(0,Random(10));
  if(Equal(Var(0),0)) Exit(Create(FLNT),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),1)) Exit(Create(SFLN),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),2)) Exit(Create(EFLN),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),3)) Exit(Create(TFLN),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),4)) Exit(Create(ADB1),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),5)) Exit(Create(FBMP),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),6)) Exit(Create(STFL),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),7)) Exit(Create(XARW),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),8)) Exit(Create(FLNT),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),9)) return(Other());
  if(Equal(Var(0),10)) Exit(Create(SPGR),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  Smoke(0,0,Sum(Random(4),6));
  Explode(Sum(Random(Sum(Random(Sum(Random(Sum(Random(10),5)),5)),5)),10));
  return(1);

Other:
  SetVar(0,Random(29));
  if(Equal(Var(0),0)) Exit(Create(QT12),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),1)) Exit(Create(QT11),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),2)) Exit(Create(QT10),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),3)) Exit(Create(QTF9),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),4)) Exit(Create(QTF8),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),5)) Exit(Create(QTF7),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),6)) Exit(Create(QTF9),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),7)) Exit(Create(QTF8),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),8)) Exit(Create(QTF7),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),9)) Exit(Create(QTF6),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),10)) Exit(Create(QTF5),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),11)) Exit(Create(QTF4),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),12)) Exit(Create(QTF6),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),13)) Exit(Create(QTF5),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),14)) Exit(Create(QTF4),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),15)) Exit(Create(QTF6),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),16)) Exit(Create(QTF5),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),17)) Exit(Create(QTF4),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),18)) Exit(Create(QTF3),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),19)) Exit(Create(QTF2),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),20)) Exit(Create(QTF1),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),21)) Exit(Create(QTF3),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),22)) Exit(Create(QTF2),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),23)) Exit(Create(QTF1),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),24)) Exit(Create(QTF3),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),25)) Exit(Create(QTF2),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),26)) Exit(Create(QTF1),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),27)) Exit(Create(QTF3),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),28)) Exit(Create(QTF2),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  if(Equal(Var(0),29)) Exit(Create(QTF1),0,0,Random(360), Sum(Random(14),-7), Sum(Random(3),-8), +10);
  Explode(Sum(Random(Sum(Random(Sum(Random(Sum(Random(10),5)),5)),5)),10));
  return(1);

Create:
  Var(0)=CreateContents(Par(0));
  SetOwner(GetOwner(),Var(0));
  return(Var(0));

Sett:
  ObjectSetAction(Par(0),"Checking");
  SetOwner(GetOwner(), Par(0));
  return(1);