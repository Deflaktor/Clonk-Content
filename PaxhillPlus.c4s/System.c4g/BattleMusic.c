/*-- Neues Objekt --*/

#strict

static battleMusicEndFrame;
static importantBattleMusicEndFrame;
static currentBattleMusic;

global Music:
  if(!Par(0)) {
    battleMusicEndFrame=0;
	importantBattleMusicEndFrame=0;
    return(inherited(Par(0), Par(1)));
  }
  if(currentBattleMusic)
    SetPlayList(Format("*%s", currentBattleMusic));
  if(FrameCounter() < battleMusicEndFrame && !Par(2))
	return(0);
  if(importantBattleMusicEndFrame)//FrameCounter() < importantBattleMusicEndFrame)
    return(0);
  var seconds=0;
  if(Par(0)S="@li'l drips.ogg")
    seconds=60+17;
  else if(Par(0)S="@oi, that pops!!!.ogg")
    seconds=60+3;
  else if(Par(0)S="@rot loaf.ogg")
    seconds=56;
  else if(Par(0)S="@Ruinion.ogg")
    seconds=58;
  else if(Par(0)S="@the fire brigade.ogg")
    seconds=60+4;
  else if(Par(0)S="@CamelsStrawsAndBacks.ogg")
    seconds=54;
  else if(Par(0)S="@ifYouCanUseADoorKnob.ogg")
    seconds=60+4;
  battleMusicEndFrame = seconds*38+FrameCounter();
  if(Par(2))
    importantBattleMusicEndFrame = battleMusicEndFrame;
  if(seconds)
    currentBattleMusic = Par(0);
  else
    currentBattleMusic = 0;
  if(currentBattleMusic)
    SetPlayList(Format("*%s", currentBattleMusic));
  return(inherited(Par(0)));

global BattleMusic:
  var randomBattleMusic;
  randomBattleMusic = Random(3);
  if(randomBattleMusic==0)
    Music("@li'l drips.ogg", 1);
  if(randomBattleMusic==1)
    Music("@oi, that pops!!!.ogg", 1);
  if(randomBattleMusic==2)
    Music("@rot loaf.ogg", 1);
  if(randomBattleMusic==3)
    Music("@the fire brigade.ogg", 1);
  return(1);
  
global PeaceMusic:
  return(SetPlayList());

global SwitchToDefaultMusic:
  importantBattleMusicEndFrame=0;
  while(Var(0)=FindObject(_DST, 0, 0, 0, 0, 0, 0, 0, 0, Var(0)))
    Var(0)->VisitorCheck();
  if(dragonBattle) {
    battleMusicEndFrame = 0;
	return(BattleMusic());
  }
  battleMusicEndFrame = 0;
  if(currentBattleMusic S= "@Ruinion.ogg")
    Music("@RuinionEnd.ogg");
  else
    Music("@CamelsStrawsAndBacksEnd.ogg");

  PeaceMusic();
  return(1);
  