
#strict

Activate:

CreateMenu(_OFE,Par(0));

AddMenuItem("Oberfläche","Oberflaeche",_OFE,Par(0));
AddMenuItem("Untergrund","Untergrund",_UTG,Par(0));
return(1);


Oberflaeche:
  Sound("Magic1");
  SetVar(0,Contained());
  ForcePosition(Var(0),GetX(FindObject(_TP2)),GetY(FindObject(_TP2)));
  SetVar(0,Contents(0,Var(9)));
  Exit(Var(0));
  return(1);


Untergrund:
  Sound("Magic1");
  SetVar(0,Contained());
  ForcePosition(Var(0),GetX(FindObject(_TP1)),GetY(FindObject(_TP1)));
  SetVar(0,Contents(0,Var(9)));
  Exit(Var(0));
  return(1);