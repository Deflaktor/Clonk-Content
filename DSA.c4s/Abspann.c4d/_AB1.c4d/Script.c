#strict

Initialize:
  SetComDir(COMD_Down());
  SetYDir(1);
  SetAction("Speak");
  return(1);

Text:
  if(GreaterThan(GetActTime(),100)) Call("Fertig");
  SetComDir(COMD_Down());
  Message("Der Sieg ist Euer!",this());
  return(1);

Fertig:
  CreateObject(_AB2);
  RemoveObject();
  return(1);