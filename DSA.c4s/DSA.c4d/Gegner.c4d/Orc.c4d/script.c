#strict

#include _GTE

Initialize:
  _inherited();
  if(Equal(Random(5),0)) CreateContents(GD3A);
  if(Equal(Random(5),0)) CreateContents(GD3A);
  if(Equal(Random(5),0)) CreateContents(GD3A);
  if(Equal(Random(5),0)) CreateContents(GD3A);
  if(Equal(Random(5),0)) CreateContents(GS3A);
  if(Equal(Random(5),0)) CreateContents(GS3A);
  if(Equal(Random(3),0)) CreateContents(GD3A);
  if(Equal(Random(8),0)) CreateContents(GD3A);
  return(1);

Power:
  return(50);
CritRate:
  return(100);
Speed:
  return(5);

WeaponSound:
  return(Sound("AxeHit*"));
Hurt:
  return(Sound("Hurt*"));
DeathSound:
  return(Sound("die_orc.wav"));

Fighting:
  return(SetAction("AxeFight",Par(0)));

AxeFighting:
  if (KannAngreifen()) return(SetAction("AxeStrike"));
  return(1);
  
AxeStrike:
  return(Strike());

Death:
  _inherited();
  ObjectCall(CreateObject(_GTT,0,10),"Sterb","Ork");
  RemoveObject();
  return(1);