/*-- Neues Objekt --*/

#strict

local zeit, stop, frame;

protected Check:
  if(!stop)
    frame++;
  if(frame>=36) {
    frame = 0;
    zeit++;
  }

  if(Global(0)==1)
    Marathon();
  if(Global(0)==2)
    Punkterennen();
  ZeigFortschritt();
  return(1);

GibPunkt:
  if(Global(0)==1)
    Local(Par(0)) = zeit;
  if(Global(0)==2)
    Local(Par(0))++;
  return(1);

Zeit:
  return(zeit);

Minuten:
  return(zeit/60);

Sekunden:
  return(zeit-Minuten()*60);

Stop:
  stop = 1;
  return(1);

Resume:
  stop = 0;
  return(1);

protected Marathon:
  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i))  {
      var obj = GetCursor(i);
      if(Local(i)==0)
        SetScore(i,zeit);
      else
        SetScore(i,Local(i));
      --j;
    }
  return(1);

protected Punkterennen:
  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i))  {
      var obj = GetCursor(i);
      SetScore(i,Local(i));
      --j;
    }
  return(1);

protected ZeigFortschritt:
  for (var i,j=GetPlayerCount(); j; ++i)
    if (GetPlayerName(i))  {
      var obj = GetCursor(i);
      if(GetX()>32600&&GetY()<200)
        SetWealth(i,100);
      else
        SetWealth(i,Min(100,100*GetX(obj)/(LandscapeWidth()-1000)));
      --j;
    }
  return(1);

protected SetScore:
  return(DoScore(Par(0),Par(1)-GetScore(Par(0))-GetWealth(Par(0))));