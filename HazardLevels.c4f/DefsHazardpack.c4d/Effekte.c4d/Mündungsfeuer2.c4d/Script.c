#strict

Start:
 SetAction("Flug",Par(0));
 SetComDir(COMD_Stop());
 SetDir(GetDir(Par(0)));
 SetLocal(0,Par(0));
 return(1);

Posi:
   SetDir(GetDir(Par(0)));
   ForcePosition(this(),Sum(GetX(Local(0)),Sum(-10,Mul(GetDir(this()),21))),Sub(GetY(Local(0),2)));
   return(1);

Weg:
 RemoveObject();
 return(1);
