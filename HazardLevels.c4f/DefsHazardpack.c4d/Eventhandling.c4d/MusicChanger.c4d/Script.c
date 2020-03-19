#strict
#include T_1_
/* MessageEvent */

local music, playList, fadeOut;
static playingMusic;

public func Copy() {
  var obj = inherited();
  obj->SetMusic(music, playList);
  return(obj);
}


protected func TargetCompatible(object pTarget) {
  return(0);
}

protected func AlternativeComment() {
  return(music);
}

protected func Execute(object pActuator) {
  if(playingMusic eq music&&playingMusic)
    return(1);
  if(!music) {
    playingMusic = "@NONE@";
    fadeOut=10;
    return(1);
  }
  playingMusic = music;
  StandardMusicLevel();
  if(playList)
    Music(music, 0);
  else
    Music(music, 1);
  SetPlayList(music);
  if(playList)
    SetPlayList();
  return(1);
}

public func SetMusic(string pMusic, bool pStandardPlayList) {
  music = pMusic;
  playList = pStandardPlayList;
  return(1);
}

protected func Timer() {
  _inherited();
  if(fadeOut) {
    if(playingMusic ne "@NONE@") {
      fadeOut=0;
      StandardMusicLevel();
      return(1);
    }
    fadeOut--;
    MusicLevel(fadeOut*5);
    if(!fadeOut) {
      Music();
      SetPlayList("");
      if(playList)
        SetPlayList();
    }
  }
  return(1);
}

StandardMusicLevel:
  return(MusicLevel(50));

IsTriggerable:
  return(1);

