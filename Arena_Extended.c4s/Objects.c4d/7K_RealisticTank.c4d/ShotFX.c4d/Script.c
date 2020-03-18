#strict

Initialize:

  // Unterwasser kommen nur Luftblasen raus
  if(GBackLiquid()) // InLiquid() funktioniert nicht.
    {
      Bubble();
      Bubble(Sin(GetR()-Random(GetR()/2),1+Random(1)),Cos(GetR()+Random(GetR()/2),1+Random(1)));
      Bubble(Sin(GetR()-Random(GetR()/2),2+Random(2)),Cos(GetR()+Random(GetR()/2),2+Random(2)));
      Bubble(Sin(GetR()-Random(GetR()/2),3+Random(3)),Cos(GetR()+Random(GetR()/2),3+Random(3)));
      Bubble(Sin(GetR()-Random(GetR()/2),4+Random(4)),Cos(GetR()+Random(GetR()/2),4+Random(4)));
      Bubble(Sin(GetR()-Random(GetR()/2),5+Random(5)),Cos(GetR()+Random(GetR()/2),5+Random(5)));
      RemoveObject();
      return(1);
    }

  Smoke(0,0,3+Random(4));
  SetAction("ExistAMoment");
  return(1);

Remove:
  RemoveObject();
  return(1);
