/*-- Sprengpfeil --*/

Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

/* Pfeileigenschaften */
public PackTo: return(XARP);
public IsArrow: return(1);

/* Produkteigenschaften */
public IsAnvilProduct: return(1);

/* Wird abgefeuert */
public Launch:
  SetAction("Shot");
  Check();
  return(1);

/* Aufschlag */
protected Hit:
  Explode(Sum(10,Random(5)));
  return(1);

/* Ziel prüfen */
private InFlight:
  while (SetVar(0,FindObject(0,+1,+1,0,0,0,0,0,NoContainer(),Var(0))))
    if (ObjectCall(Var(0),"IsArrowTarget"))
      return(HitTarget(Var(0)));
  return(1);

/* Treffer */
private HitTarget:
  Explode(Sum(10,Random(5)));
  return(1);

/* Forschung */

public GetResearchBase: return(FARW);