#strict

#include _GTE

Power:
  return(30);
CritRate:
  return(100);
Speed:
  return(5);

WeaponSound:
  return(Sound("SwordHit*"));
Hurt:
  return(Sound("Demonhit.wav"));
DeathSound:
  return(Sound("DemonDie.wav"));

Fighting:
  return(SetAction("SwordFight",Par(0)));

SwordFighting:
  if (KannAngreifen()) {
    if (Random(2))
      return(SetAction("SwordStrike"));
    else
      return(SetAction("Peitsch"));
  }
  return(1);

Death:
  _inherited();
  SetLocal(1,1,FindObject(FT31,-4000,-4000,8000,8000));
  SetLocal(1,1,FindObject(FT32,-4000,-4000,8000,8000));
  SetLocal(1,1,FindObject(FT33,-4000,-4000,8000,8000));
  return(1);
