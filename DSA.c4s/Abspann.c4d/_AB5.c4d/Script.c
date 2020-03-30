#strict

Initialize:
  SetComDir(COMD_Down());
  SetYDir(1);
  SetAction("Speak");
  return(1);

Text:
  if(GreaterThan(GetActTime(),5000)) Call("Fertig");
  SetComDir(COMD_Down());
  GameOver();
  return(1);

Fertig:
  RemoveObject();
  return(1);