Initialize:
  CreateContents(HC3A);
  CreateContents(HB3A);
  CreateContents(ZC3A);
  CreateContents(OE3A);
  CreateContents(SP3A);
  CreateContents(GL3A);
  SetAction("Wait");
  return(1);

ControlUp:
  SetLocal(0,Par(0));
  if ( SEqual ( GetAction() , "Ready" ) ) Call("Hallo","Was wünschet Ihr?");
  return(1);

Hallo:
  Message("%s",this(),Par(0));
  Call("Auswahl1");
  return(1);


Auswahl1:
  SetAction("Wait");
  CreateMenu(0,Local(0),this(),2,"Sucht euch etwas aus.");
  while (SetVar(1,FindObject(0,0,0,0,0,0,0,0,this(),Var(1))))  if(SetVar(2,GetID(Var(1))))  AddMenuItem( "%s", "Sortieren", Var(2),Local(0) ); 

  return(1);

Sortieren:
  SetVar(1,GetValue(FindContents(Par(0))));
  if(LessThan(GetWealth(0),Var(1))) Call("Hallo","Ihr könnt euch das nicht leisten.");
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
 

AlleNull:
  SetLocal(0,0);
  SetLocal(1,0);
  SetLocal(2,0);
  SetLocal(3,0);
  SetLocal(4,0);
  SetLocal(5,0);
  SetLocal(6,0);
  SetLocal(7,0);
  SetLocal(8,0);
  SetLocal(9,0);
  return(1);
