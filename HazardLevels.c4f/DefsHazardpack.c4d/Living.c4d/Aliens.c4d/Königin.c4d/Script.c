#strict
#include _KI_


Initialize:
  Refit();
  if(Global(6)) return(1);
  SetVar(0,CreateConstruction(WS5B,0,3,-1,1));
  SetLocal(0,this(),Var(0));
  return(1);

Activity:
  _inherited();
  if(GetAction() eq "Frozen") return(1);
  if(FindObject(0,-500,-100,1000,200,OCF_CrewMember(),0,0,NoContainer()))
    if (!GetVisibility(Var(0)))
      Angriff();
  if(Global(6))
    if(Not(Random(((Global(5)+100)/5)*Sqrt(Local(0,FindObject(ST5_))+1)))) Stippel();
  if(Not(Equal(GetCon(),100)))          return(0);
  if(FindObject(MF5B,-25,-25,50,50))	return(0);
  if(Random(Mul(10,ObjectCount(MF5B)))) return(0);
  if(Not(Global(2)))                    return(0);
  return(SetAction("Auf"));

Bluten:
  if(!Global(0))
  return(2);
  if(Par(0)==0)
  CastObjects(BL7K,20,20);
  if(Par(0)!=0)
  CastObjects(BL7K,Par(0),20);
  return(1);

Angriff:
  while (SetVar(0, FindObject(ST5B,0,0,0,0,0, 0,0, 0, Var(0)) ))
    {
     SetVar(1,FindObject(0,-500,-100,1000,200,OCF_CrewMember(),0,0,NoContainer()));
     if(Var(1)) if (!GetVisibility(Var(0))) SetLocal(1,Var(1),Var(0));
    };
  return(1);

Geburt:
  if(LessThan(GetEnergy(),1)) return(Stippelschleuder());
  if(Local(0)) return(Erbrechen());
  if(Not(Global(2))) return(0);
  CreateObject(MF5B,0,0,GetOwner());
  return(Sound("KGGeburt"));

Erbrechen:
  return(); //Soll nix schleudern. Aber ganz rausnehmen will ich das erstmal nicht.
  SetVar(0,CreateContents(ACID));
  SetVar(1,FindObject(0,0,0,-1,-1,OCF_CrewMember()));
  SetVar(2,Div(Sub(GetX(Var(1)),GetX()),25));
  SetVar(3,-3);
  SetVar(4,Mul(Var(2),10));
  Exit(Var(0),0,0,0,Var(2),Var(3),Var(4));
  SetLocal(0,0);
  return(Sound("KGGeburt"));

Stippelschleuder:
  SetVar(0,FindObject(0,0,0,-1,-1,OCF_CrewMember()));
  ObjectCall(CreateObject(ST5B,0,3,GetOwner()),"Angriff",Var(0));
  DoCon(-10);
  SetAction("Auf");
  Sound("KGGeburt");
  if(Not(Equal(GetCon(),50))) return(0);
  CreateObject(ST5B,0,3,GetOwner());
  return(RemoveObject());

Stippel:
  ObjectCall(CreateObject(ST5B,0,0,GetOwner()),"Frisch");
  Sound("KGGeburt");
  return(1);

CatchBlow:
  return(Damage());

Damage:
  Bluten(Par(0));
  if(Local(0)) return(0);
  SetLocal(0,1);
  return(SetAction("Auf"));

Death:
  return(SetAction("Auf"));