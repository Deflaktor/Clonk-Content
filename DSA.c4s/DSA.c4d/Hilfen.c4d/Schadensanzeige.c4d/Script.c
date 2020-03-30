/*-- Neues Objekt --*/

#strict

protected Initialize:
  return(1);

//Var(0) = Schaden
//Var(1) = Modulo-Wert, z.B. 100 oder 10
//Var(2) = Schaden % Modulo-Wert um die bestimmte Ziffer zu kriegen
//Var(3) = X-Wert zu Positionieren
//Schaden: 584
Go:
  SetVar(6,GetX());
  SetVar(7,10);
  while(FindObject(_ZIF,-15,-10,30,20)) {
    SetPosition(Var(6)-Var(7)/2+Random(Var(7)),GetY());
    SetVar(7,Var(7)+10);
  }
  SetVar(0,Local(0));
  while(Var(0)>0) {
    SetVar(0,Var(0)/10);
    SetVar(3,Var(3)+5);
  }
  SetVar(0,Local(0));
  while(Var(0)>0) {
    SetVar(2,Var(0)%10);
    SetVar(4,CreateObject(_ZIF,Var(3)));
    ObjectCall(Var(4),"Set",Var(2));
    SetVar(0,Var(0)/10);
    SetVar(3,Var(3)-10);
  }
  return(RemoveObject());