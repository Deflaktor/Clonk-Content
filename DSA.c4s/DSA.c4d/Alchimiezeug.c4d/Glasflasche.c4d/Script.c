Hit:
  Sound("bottle");
  if(Equal(Random(5),0)) Call("bruchsicheristsienicht");
  return(1);

bruchsicheristsienicht:
  Sound("PengKlirr.wav");
  RemoveObject();
  return(1);