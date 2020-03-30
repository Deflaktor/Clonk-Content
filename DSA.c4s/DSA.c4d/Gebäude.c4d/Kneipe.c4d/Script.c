#strict
local obj;

Initialize:
  SetAction("Wait");
  CreateContents(BRED);
  CreateContents(CBRD);
  CreateContents(COKI);
  CreateContents(MCHK);
  CreateContents(_I02);
  CreateContents(_I04);
  CreateContents(_F05);
  SetAction("Wait");
  return(1);

ActivateEntrance:
  SetLocal(0,Par(0));
  SetCommand(Par(0),"none");
  if(Not(Equal(Local(1),4)))  if(SEqual(GetAction(),"Ready")) Call("Hallo","Ja, was wollt ihr?");
  return(1);

Hallo:
  Message("%s",this(),Par(0));
  Call("Auswahl1");
  return(1);

Auswahl1:
  SetAction("Wait");
  if(Not(Equal(Local(1),10))) CreateMenu(0,Local(0),this());
  if(Equal(Local(1),0))  AddMenuItem("Ich will etwas verkaufen","SellIt",_M08,Local(0));
  if(Local(3))  AddMenuItem("Was war nochmal links vom Haifischsee?","Haifischsee",_M04,Local(0));
  if(Equal(Local(1),0))  AddMenuItem("Gibts was neues?","Wasneues",_M01,Local(0));
  return(1);

SellIt:
  CreateMenu(0,Local(0),this(),2,"Was wollt ihr verkaufen?",0,0,0);
  while(obj=FindObject(0,0,0,0,0,0,0,0,Local(0),obj)) 
    if(NichtsWertvolles(GetID(obj))) 
      if(GetValue(obj)>0)  
        AddMenuItem(Format("%s",GetName(obj),GetValue(obj)),"NowSell",GetID(obj),Local(0),0,obj);
  return(1);

NowSell:
  SetWealth(0,GetWealth(0)+GetValue(Par(1)));
  Message("Gut ich nehm's! Hier hast du deine %d Goldmünzen!",this(),GetValue(Par(1)));
  RemoveObject(Par(1));
  SellIt();
  return(1);

Haifischsee:
  Call("Hallo","Ich habe von den Gästen gehört, dass es links vom Haifischsee eine Höhle mit einer magischen Esse gibt.| Diese schmiedet dir einen mächtigen Magierstab, wenn du drei heilige Edelsteine dabei hast. |Um da aber rüberzukommen brauchst du ein Boot.");
  return(1);

Wasneues:
  if(Local(3)==0) {
    Haifischsee();
    SetLocal(3,1);
    SetVar(0,FindObject(_S10));
    SetLocal(1,Local(1,Var(0))|1,Var(0));
  } else 
    Call("Hallo","Nein. Alles beim Alten. Gäste kommen und fressen sich voll, und unser Bier ist wieder knapp,| also wie immer!");
  return(1);

Auswahl2:
  SetAction("Wait");
  CreateMenu(0,Local(0),this());
  while (SetVar(1,FindObject(0,0,0,0,0,0,0,0,this(),Var(1))))  if(SetVar(2,GetID(Var(1))))   AddMenuItem( "%s", "Sortieren", Var(2),Local(0) ); 

  return(1);

NichtsWertvolles:
  if(Par(0)==MB3A) return(0);
  if(Par(0)==KO3A) return(0);
  if(Par(0)==EX3A) return(0);
  if(Par(0)==ZS3A) return(0);
  if(Par(0)==MT3A) return(0);
  if(Par(0)==AC3A) return(0);
  if(Par(0)==BO3B) return(0);
  if(Par(0)==_RZS) return(0);
  if(Par(0)==_ZKI) return(0);
  if(Par(0)==_ZKR) return(0);
  if(Par(0)==_ZKH) return(0);
  return(1);

PayMuch:
  //Das anderthalbfache des Preises berechnen.
  return(Div(Mul( GetValue(FindContents(Par(0))),3),2));

Sortieren:
  SetVar(1,GetValue(FindContents(Par(0))));
  if(LessThan(GetWealth(0),Var(1))) Call("Hallo","Wollt ihr mich verarschen? Besorgt euch erst mal das Geld!");
  if(GreaterThan(GetWealth(0), Sub(Var(1),1) )) Call("Kaufen",Par(0),Var(1));
  return(1);


Kaufen:
  //Par(0) ist die ID des Artikels
  //Par(1) sind die Kosten
  if(Not(Par(0))) return(0);
  SetWealth(0,Sub(GetWealth(0),Par(1)));
  Sound("uncash.wav");
  CreateObject(Par(0),0,12);
  return(1);
