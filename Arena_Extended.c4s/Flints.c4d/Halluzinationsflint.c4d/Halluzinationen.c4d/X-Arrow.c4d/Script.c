/* Pfeileigenschaften */
public PackTo: return(XARP);
public IsArrow: return(1);

/* Produkteigenschaften */
public IsAnvilProduct: return(1);

/* Wird abgefeuert */
public Launch:
  SetAction("Shot");
  return(1);

/* Aufschlag */
protected Hit:
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  RemoveObject();
  return(1);

/* Ziel prüfen */
private InFlight:
  while (SetVar(0,FindObject(0,+1,+1,0,0,0,0,0,NoContainer(),Var(0))))
    if (ObjectCall(Var(0),"IsArrowTarget"))
      return(HitTarget(Var(0)));
  return(1);

/* Treffer */
private HitTarget:
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  RemoveObject();
  return(1);