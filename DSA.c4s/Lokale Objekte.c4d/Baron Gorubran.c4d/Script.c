Initialize:
  SetEntrance(1);
  CreateContents(GD3A);
  SetAction("Walk");
  return(1);

Fighting:
  return(SetAction("KnifeFight",Par(0)));

KnifeFighting:
  if (Not(Random(4))) return(SetAction("KnifeStrikeoben"));
  if (Not(Random(4))) return(SetAction("KnifeStrikeunten"));
  return(1);
  
KnifeStrike:
  if(Equal(Random(2),0)) Call("Magic","Teleport");
  if (Not(Random(2))) return(1);
	SetVar(0, 12);
	if (HasShield(GetActionTarget())) SetVar(0, 8);
  Punch(GetActionTarget(),Var(0));
  return(1);

HasShield:
  return (FindObject(SHIA,0,0,0,0,0,"Shield",Par(0)));

FightProcess:
  if(Random(2)) return(1);
  SetAction("Punch");
  return(1);

Punch:
  if(Not(Random(3))) Sound("Kime*");
  if(Not(Random(5))) Sound("Punch*");
  if(Not(Random(2))) return(1);
  Punch(GetActionTarget());
  return(1);
CatchBlow:
  if (SEqual(GetAction(),"Dead")) return(0);
  if(Not(Random(5))) Call("Hurt");
  return(1);
Hurt:
  Sound("Hurt*");
  return(1);
Death:
  Sound("Die");
  CreateObject(KT3A,0,10);
  RemoveObject();
  return(1);
DeepBreath:
  Sound("Breath");
  return(1);
Redefine:
  ChangeDef(Par(0));
  SetAction("Walk");
  return(1);

ZielOK:
  SetVar(1,Random(2));
  SetVar(2,Random(3));

 //----X-Wert für Teleport
  if(Equal(Var(1),0)) SetLocal(8,750);
  if(Equal(Var(1),1)) SetLocal(8,1050);

 //----Y-Wert für Teleport
  if(Equal(Var(2),0)) SetLocal(9,200);
  if(Equal(Var(2),1)) SetLocal(9,240);
  if(Equal(Var(2),2)) SetLocal(9,290);


  SetVar(3,Random(2));
  SetVar(4,Random(2));  

 //----X-Wert für Bogenschützen
  if(Equal(Var(3),0)) SetLocal(6,773);
  if(Equal(Var(3),1)) SetLocal(6,1033);
  SetLocal(6,Sub(Local(6),GetX()));

 //----Y-Wert für Bogenschützen
  if(Equal(Var(4),0)) SetLocal(7,240);
  if(Equal(Var(4),1)) SetLocal(7,290);
  SetLocal(7,Sub(Local(7),GetY()));

  return(1);

SelectAttack:
  SetVar(0,Random(5));
  if(Equal(Var(0),0)) SetVar(1,BF3A);  //Band und Fessel
  if(Equal(Var(0),1)) SetVar(1,FM3A);  //Fulminictus
  if(Equal(Var(0),2)) SetVar(1,IG3A);  //Ignifaxius
  if(Equal(Var(0),3)) SetVar(1,IG3A);  //Ignifaxius
  if(Equal(Var(0),4)) SetVar(1,GV3A);  //Grosse Verwirrung
  return(Var(1));

SelectWarrior:
  SetVar(0,Random(12));
  if(LessThan(Var(0),5)) return(0);
  if(Equal(Var(0),5))  SetVar(1,KB3A);
  if(Equal(Var(0),6))  SetVar(1,KB3A);
  if(Equal(Var(0),7))  SetVar(1,KB3A);
  if(Equal(Var(0),8))  SetVar(1,KB3A);
  if(Equal(Var(0),9))  SetVar(1,KA3A);
  if(Equal(Var(0),10))  SetVar(1,KA3A);
  if(Equal(Var(0),11))  SetVar(1,KS3A);
  return(Var(1));

ErschaffeGegner:
  SetVar(1,SelectWarrior());
  SetLocal(6,Sub(900,GetX()));
  SetLocal(7,Sub(170,GetY()));
  if(Equal(Var(1),KB3A)) if(Call("ZielOK"))  if(FindObject(KB3A,Sub(Local(6),20),Sub(Local(7),20),40,40)) Call("ZielOK");
  if(Equal(Var(1),KB3A)) if(FindObject(KB3A,Sub(Local(6),20),Sub(Local(7),20),40,40)) return(0);
  CreateObject(Var(1),Local(6),Local(7));
  return(1);


Magic:
  if(SEqual(GetAction(),"KnifeFight")) return(0);
  SetAction("Zaubern");
  if(SEqual(Par(0),"FertigBrennen"))  SetLocal(5,1);
  if(SEqual(Par(0),"Teleport")) if(ZielOK())  SetLocal(5,2);
  if(SEqual(Par(0),"Attacke"))  SetLocal(5,3);
  if(SEqual(Par(0),"Summon"))  SetLocal(5,4);
  if(SEqual(Par(0),"Defend"))  SetLocal(5,5);
  return(1);

Zauberfertig:
  if(Equal(GetDir(),DIR_Right()))  SetVar(1,7);
  if(Equal(GetDir(),DIR_Left()))  SetVar(1,-7);
  if(Equal(Local(5),1))  Extinguish();
  if(Equal(Local(5),2))  SetPosition(Local(8),Local(9));
  if(Equal(Local(5),3))  ObjectCall(CreateObject(SelectAttack(),Var(1)),"Activate",this());
  if(Equal(Local(5),4))  Call("ErschaffeGegner");
  if(Equal(Local(5),5))  Call("KillZauber",Par(1));
  return(1);


KillZauber:
  RemoveObject(Par(0));
  CreateObject(DT3A,Sub(GetX(Par(0)),GetX()),Sub(GetY(Par(0)),GetY()),GetOwner(Par(0)));
  return(1);

Test:
  if(Not(SEqual(GetAction(),"Zaubern")))
   if(Not(SEqual(GetAction(),"KnifeFight")))
    if(Not(SEqual(GetAction(),"GetPunched")))
     if(Not(SEqual(GetAction(),"Punch")))
      if(Not(SEqual(GetAction(),"KnifeStrike")))
       Call("Abfrage");
  return(1);


Abfrage:

 //----Ausrichtung auf X-wert 900 und je nach Ausrichtung andere Abfragen
  if(GreaterThan(GetX(),900)) Call("DrehungLinks");
  if(LessThan(GetX(),900)) Call("DrehungRechts");

  return(1);

DrehungRechts:
  SetDir(DIR_Right());

  //----Löschen
  if(OnFire())  Call("Magic","FertigBrennen");

  //ist einer zu nah?
  if(FindObject(0,-20,-20,50,30,OCF_Prey())) Call("Magic","Teleport");

  ////Werde ich durch einen Zauber angegriffen?
  //if(SetVar(1,FindObject(IG3A,0,-20,150,60))) Call("Magic","Defend",Var(1));
  //if(SetVar(1,FindObject(FM3A,0,-20,150,60))) Call("Magic","Defend",Var(1));

  //Sonst ein Ziel?
  if(FindObject(0,-180,-40,360,70,OCF_Prey())) Call("Magic","Attacke");

  //Dann machen wir was zufälliges
  SetVar(0,Random(10));
  if(LessThan(Var(0),4)) return(0);
  if(Equal(Var(0),4)) Call("Magic","Summon");
  if(Equal(Var(0),5)) Call("Magic","Summon");
  if(Equal(Var(0),6)) Call("Magic","Summon");
  if(Equal(Var(0),7)) Call("Magic","Teleport");
  if(Equal(Var(0),8)) Call("Magic","Teleport");
  if(Equal(Var(0),9)) Call("Magic","Teleport");
  return(1);

DrehungLinks:
  SetDir(DIR_Left());

  //----Löschen
  if(OnFire())  Call("Magic","FertigBrennen");

  //ist einer zu nah?
  if(FindObject(0,-30,-20,50,30,OCF_Prey())) Call("Magic","Teleport");

  ////Werde ich durch einen Zauber angegriffen?
  //if(SetVar(1,FindObject(IG3A,150,-20,150,60))) Call("Magic","Defend",Var(1));
  //if(SetVar(1,FindObject(FM3A,150,-20,150,60))) Call("Magic","Defend",Var(1));

  //Sonst ein Ziel?
  if(FindObject(0,-180,-40,360,70,OCF_Prey())) Call("Magic","Attacke");

  //Dann machen wir was zufälliges
  SetVar(0,Random(10));
  if(LessThan(Var(0),4)) return(0);
  if(Equal(Var(0),4)) Call("Magic","Summon");
  if(Equal(Var(0),5)) Call("Magic","Summon");
  if(Equal(Var(0),6)) Call("Magic","Attacke");
  if(Equal(Var(0),7)) Call("Magic","Teleport");
  if(Equal(Var(0),8)) Call("Magic","Teleport");
  if(Equal(Var(0),9)) Call("Magic","Teleport");
  return(1);

Nahkampf:
  if(SEqual(GetAction(),"KnifeFight")) return(0);
  if(SEqual(GetAction(),"KnifeStrike")) return(0);
  if(And(SetVar(0,FindObject(MA3A,-12,-10,24,20,0,0,0,NoContainer())),GetAlive(Var(0)))) if(Not(Equal(Local(7,Var(0)),1))) Fight(Var(0));
  if(And(SetVar(0,FindObject(WL3A,-12,-10,24,20,0,0,0,NoContainer())),GetAlive(Var(0)))) if(Not(Equal(Local(7,Var(0)),1))) Fight(Var(0));
  if(And(SetVar(0,FindObject(KR3A,-12,-10,24,20,0,0,0,NoContainer())),GetAlive(Var(0)))) if(Not(Equal(Local(7,Var(0)),1))) Fight(Var(0));
  return(1);

Fight:
  if(Not(GetAlive(Par(0)))) return(1);
  SetAction("Fight",Par(0));
  ObjectSetAction(Par(0),"Fight",this());
  return(1);


