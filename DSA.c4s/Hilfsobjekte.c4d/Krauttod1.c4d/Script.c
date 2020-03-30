Initialize:
  SetAction("Los");
  return(1);

Test:
  SetVar(1,ObjectCount(ES3A));

  while(GreaterThan(Var(1),25))  if(DecVar(1)) RemoveObject(FindObject(ES3A));

  SetPosition(Random(LandscapeWidth()),Random(LandscapeHeight()));


  return(1);