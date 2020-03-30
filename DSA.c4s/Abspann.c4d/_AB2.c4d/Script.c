#strict

Initialize:
  Music("rivasnd.mid");
  SetComDir(COMD_Down());
  SetYDir(1);
  SetAction("Speak");
  return(1);

Text:
  if(GreaterThan(GetActTime(),100)) Call("Fertig");
  SetComDir(COMD_Down());
  Message("Die Armee des Barons ist angesichts seines Todes nicht mehr in der Lage, zu funktionieren.",this());
  return(1);

Fertig:
  CreateObject(_AB3);
  RemoveObject();
  return(1);