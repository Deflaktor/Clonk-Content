protected Hit:
  Explode(Sum(Random(35),35));
  CastObjects(SPRK,8,50);
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  Smoke(0,0,Sum(Random(4),6));
  return(1);

/* Produkteigenschaften */

public IsChemicalProduct: return(1);

/* Forschung */

public GetResearchBase: return(QTF5);