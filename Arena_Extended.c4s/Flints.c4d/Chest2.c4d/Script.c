#strict
#include PRNT

Initialize:
  SetAction("SetColor");
  return(1);

//ruft der Clonk beim werfen auf, aber hier gibts den Befehl nicht
Check:
  return(1);

SetMyColor:
  if(GetOwner()==-1)
    SetColorDw(RGBa(255, 255, 255, 0));
  return(1);

Entrance:
  if(GetAction() S= "Zielsuchen")
    return(Exit());
  if(GetAction() S= "Idle")
    SetOwner(GetOwner(Par(0)),this());
  return(1);

NoShiftOwner:
  return(!(GetAction()S="Idle"));

Hit:
  if(SEqual(GetAction(),"Idle"))
    SetAction("Aufblasen");
  return(1);

Blasen:
  DoCon(1);
  if (GetCon()>200)
  return(Remove());
  return(1);

Remove:
  if(SEqual(GetAction(),"Aufblasen"))
    for(var i = 0; i<10; i++)
{
  SetVar(0,CreateObject(CHS2,0,0));
  ObjectSetAction(Var(0),"Zielsuchen");
  SetSpeed(Sub(Random(200),100),Sub(Random(400),350),Var(0));
  SetOwner(GetOwner(),Var(0));
  ObjectCall(Var(0), "SetMyColor");
}
  Explode(20);
  return(RemoveObject());

Zielsuch:
  if(SetVar(0,FindObject(0,0,0,-1,-1,OCF_Living()))) CheckSog(Var(0));
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) CheckAlive(Var(0));
  if(GreaterThan(GetActTime(this()),700)) return(RemoveObject());
return(1);

CheckAlive:
if(!GetAlive(Par(0))) return(1);
if(GetAction(Par(0)) S= "Dead") return(1);
if (GetOwner()==GetOwner(Par(0))) return(1);
Remove();
return(0);
    

CheckSog:
if(!GetAlive(Par(0))) return(1);
if(GetAction(Par(0)) S= "Dead") return(1);
/*if (!PathFree(GetX(),GetY(),GetX(Par(0)),GetY(Par(0))))
return(1);*/
if (GetOwner()==GetOwner(Par(0)))
return(1);
//if (BitAnd(OCF_CrewMember(),GetOCF(Par(0))))
SetVar(1,Div(Sub(GetX(),GetX(Par(0))),Sub(-1,Random(10))));
SetVar(2,Div(Sub(GetY(),GetY(Par(0))),Sub(-1,Random(10))));
SetSpeed(Var(1),Var(2));
return(0);