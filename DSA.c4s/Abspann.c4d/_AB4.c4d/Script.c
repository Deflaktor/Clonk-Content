#strict

Initialize:
  SetComDir(COMD_Down());
  SetYDir(1);
  SetAction("Speak");
  DoScore(0,Global(9));
  DoScore(1,Global(9));
  DoScore(2,Global(9));
  return(1);

Text:
  if(GreaterThan(GetActTime(),100)) Call("Fertig");
  SetComDir(COMD_Down());
  Message("Ihr bekommt auch eure Belohnung ausbezahlt.",this());
  return(1);

Fertig:
  CreateObject(_AB5);
  RemoveObject();
  return(1);