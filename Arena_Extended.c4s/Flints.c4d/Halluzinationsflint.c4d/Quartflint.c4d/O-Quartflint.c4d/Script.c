protected Hit:
  Explode(Sum(Random(40),40));
  CastObjects(SPRK,8,50);
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  return(1);

/* Produkteigenschaften */

public IsChemicalProduct: return(1);

/* Forschung */

public GetResearchBase: return(QTF6);