#strict
#include PRNT

Launch:  
  SetAction("Implode");
  SetLocal(2,CreateObject(SLRO,0,0,-1));
  ObjectCall(Local(2), "Connect", this(), Par(0));
  DigFree(GetX(),GetY(),30);
  return(1);
  
Zap:
  if(!Local(2))
    RemoveObject();
  Local(0)++;
  if(Local(0)>50)
    RemoveObject();
  while(SetVar(0,FindObject(0,-200,-200,400,400,0,0,0,NoContainer(),Var(0))))
    if(Or(
          // Beim suchen wird diese Reihenfolge eingehalten. Soll heißen, wenn ein Clonk neben einem Panzer steht, wird zuerst der Clonk attackiert
          BitAnd(GetOCF(Var(0)),OCF_CrewMember()),
          BitAnd(GetOCF(Var(0)),OCF_Living()),
          Equal(GetID(Var(0)),_DRN)
          ))
      // Weg Frei
      if(PathFree(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))))
      // Gehört nicht dem Spieler
      if(Not(Equal(GetOwner(Contained()), GetOwner(Var(0)) )) )
        // Lebt noch
        if(GetAlive(Var(0)))
          // Zappen!
          ObjectCall(CreateObject(HLRO,0,0,-1), "Launch",this(),Var(0),Local(2));
  return(1);