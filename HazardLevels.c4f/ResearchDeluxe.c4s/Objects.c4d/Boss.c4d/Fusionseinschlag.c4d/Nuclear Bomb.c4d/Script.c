/*-- Neues Objekt --*/

#strict

static lgt_enlightment; // Globale Erhellung durch Blitze
static lgt_last_lgt_frame; // Letztes Frame, in dem die Helligkeit angepasst wurde
local rot;
local timer;

protected Initialize:
  Music("@smetbatl",1);
  TimerSetCompleted();
  CreateObject(_RMB);
  rot=256/4;
  SetGamma(RGB(rot, 0, 0), RGB(128+rot/2, 128-rot/2, 128-rot/2), RGB(255, 255-rot, 255-rot), 5);
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
  timer = 120;
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
  Var(1)=0;
  while(SetVar(0,FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,0,Var(0))))
    if(GetAlive(Var(0)))
	  Var(1)++;
  if(Var(1)==0)
    CreateObject(EDGE);
  Rumble(0,0,LandscapeWidth(),LandscapeHeight(), 10, 20);
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
  if((minutes==0)&&(seconds<=11)) CreateObject(SDS2);
  // if((minutes==0)&&(seconds<=2)) for(var i=0; i<GetPlayerCount(); i++) SetPlrView(i,this());
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
  Music();
  LightningEffect(5000);
  ObjectCall(CreateObject(FXPE),"Activate",this());
  SetAction("Idle");
  return(1);

DestroyIt:
  return(1);

private func LightningEffect(strength)
  {
  lgt_enlightment+=strength;
  return(ExecLgt());
  }


private func ExecLgt()
  {
  // Lichteffekt ausführen (Rampe 5)
  if (lgt_enlightment>0 && lgt_last_lgt_frame != FrameCounter())
    {
    var lgt=Min(lgt_enlightment*3, 255);
    SetGamma(RGB(Min(255,rot+lgt), lgt, lgt), RGB(Min(255,128+rot/2+lgt), Min(255,128-rot/2+lgt), Min(255,128-rot/2+lgt)), RGB(255, 255-rot, 255-rot), 5);
    lgt_enlightment=Max(lgt_enlightment*4/8-1); lgt_last_lgt_frame=FrameCounter();
    }
  }
