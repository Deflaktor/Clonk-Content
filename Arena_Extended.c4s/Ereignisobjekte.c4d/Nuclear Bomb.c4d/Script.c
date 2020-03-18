/*-- Neues Objekt --*/

#strict

local timer;

protected Initialize:
  TimerSetCompleted();
  return(1);

Hit:
  Sound("RockHit*");
  return(1);

protected ControlDigDouble:
  if(Not(Equal(GetOwner(Contained()),GetOwner(this())))) return(1);
  if(Equal(GetAction(),"Activated")) return(SetAction("Idle"));
  SetAction("Activated");
  return(1);

private func TimerSetCompleted()
  {
  timer = 30;
  var seconds;
  var minutes;
  seconds = timer;
  while(seconds>=60)
    {
    seconds = (seconds-60);
    minutes = (minutes+1);
    }
  if(seconds<10)
    seconds = Format("0%d",seconds);
  if(GetType(seconds)!=C4V_String())
    if(seconds>=10)
      seconds = Format("%d",seconds);
  return(1);
  }

private func CountDownExec()
  {
  var seconds;
  var minutes;
  // Die Zeit ist abgelaufen ;(
  if(timer==0)
    {
    BlowUp();
    Message(" ");
    return(1);
    }
  // Die Zeit läuft noch
  seconds = timer;
  --timer;
  // Zählerwerte ermitteln
  while(seconds>=60)
    {
    seconds = (seconds-60);
    minutes = (minutes+1);
    }
  // Globales Geräusch ab 10 Sekunden abspielen
  if((minutes==0)&&(seconds<=10)) Sound("BIP2",1);
  //if((minutes==0)&&(seconds<=2)) for(var i=0; i<GetPlayerCount(); i++) SetPlrView(i,this());
  // Endbearbeitung
  if(seconds<10)
    seconds = Format("0%d",seconds);
  if(GetType(seconds)!=C4V_String())
    if(seconds>=10)
      seconds = Format("%d",seconds);
  // Globale Meldung ausgeben;
  Message("Nuklearexplosion in:|%d:%s",0,minutes,seconds);
  return(1);
  }


BlowUp:
  Sound("NukeBomb",1);
  Sound("Nuke",1);
  MusicLevel(0);
  CreateObject(EXCO,0,0,GetOwner());
  return(RemoveObject());  
