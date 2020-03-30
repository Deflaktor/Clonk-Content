#strict

#include _GTE

Initialize:
  _inherited();
  if(Equal(Random(4),0)) CreateContents(GD3A);
  if(Equal(Random(4),0)) CreateContents(GD3A);
  if(Equal(Random(4),0)) CreateContents(GS3A);
  if(Equal(Random(4),0)) CreateContents(GS3A);
  if(Equal(Random(3),0)) CreateContents(GS3A);
  if(Equal(Random(3),0)) CreateContents(GS3A);
  if(Equal(Random(2),0)) CreateContents(GS3A);
  if(Equal(Random(2),0)) CreateContents(GS3A);
  if(Equal(Random(4),0)) CreateContents(SP3A);
  return(1);

Power:
  return(15);
CritRate:
  return(10);
Speed:
  return(5);

WeaponSound:
  return(Sound("SwordHit*"));
Hurt:
  return(Sound("Hurt*"));
DeathSound:
  return(Sound("die_skel.wav"));

Fighting:
  return(SetAction("SwordFight",Par(0)));

SwordFighting:
  if (KannAngreifen()) {
    if (Random(2))
      return(SetAction("SwordStrike"));
    else
      return(SetAction("SwordThrust"));
  }
  return(1);

SwordStrike:
  return(Strike());

Death:
  _inherited();
  ObjectCall(CreateObject(_GTT,0,10),"Sterb","Skelett");
  return(1);