// Local 0: XDir
// Local 1: YDir
// Local 2: Zeit bis Removen
#strict
#include _POV

Dmg: return(DefinitionCall(_AM7, "Dmg"));

/* Wird abgefeuert, Par(0) ist Schußrichtung */
Launch:  
  SetLocal(2,600+Random(400));
  SetAction("Travel");
  return(1);

Hit:
  Sound("Plumps");
  return(SetAction("CauseDamage"));

Dangerous:
  if(Var(0)=SearchTarget(80))
    if(Random(2))
      Harm(Var(0));
  if(GetActTime()>Local(2)) return(RemoveObject());
  return(1);

Harm:
  Var(0) = Angle(GetX(),GetY(),GetX(Par(0)),GetY(Par(0)));
  Var(1) = CreateObject(_AM7,0,0,GetOwner());
  ObjectSetAction(Var(1), "Travel");
  SetLocal(0,Sin(Var(0),100),Var(1));
  SetLocal(1,-Cos(Var(0),100),Var(1));
  RemoveObject();
  return(1);

Damage: 
if(Par(0)>5)
  RemoveObject();
return(1);