protected Initialize:
  SetVar(0,Sub(Random(80),40) );
  SetXDir(-50+Random(100));
  SetYDir(-50+Random(100));
  SetRDir(60);
  return(1);

MakeSmaller:
  DoCon(-5);
  return(1);