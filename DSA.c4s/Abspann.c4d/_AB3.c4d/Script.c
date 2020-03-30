#strict

Initialize:
  SetComDir(COMD_Down());
  SetYDir(1);
  SetAction("Speak");
  return(1);

Text:
  if(GreaterThan(GetActTime(),100)) Call("Fertig");
  SetComDir(COMD_Down());
  Message("Als Ihr im Dorf ankommt, werdet Ihr mit einer Feier empfangen.",this());
  return(1);

Fertig:
  CreateObject(_AB4);
  RemoveObject();
  return(1);