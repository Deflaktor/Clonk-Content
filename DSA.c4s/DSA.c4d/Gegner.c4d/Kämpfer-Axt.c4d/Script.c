#strict

#include _GTE

Initialize:
  _inherited();
  if(Equal(Random(5),0)) CreateContents(GD3A);
  if(Equal(Random(5),0)) CreateContents(GD3A);
  if(Equal(Random(5),0)) CreateContents(GS3A);
  if(Equal(Random(5),0)) CreateContents(GS3A);
  if(Equal(Random(5),0)) CreateContents(GS3A);
  if(Equal(Random(5),0)) CreateContents(GS3A);
  if(Equal(Random(3),0)) CreateContents(GS3A);
  if(Equal(Random(5),0)) CreateContents(SP3A);
  return(1);

Power:
  return(15);
CritRate:
  return(100);
Speed:
  return(10);

WeaponSound:
  return(Sound("AxeHit*"));
Hurt:
  return(Sound("Hurt*"));
DeathSound:
  return(Sound("Die"));

Fighting:
  return(SetAction("AxeFight",Par(0)));

AxeFighting:
  if (KannAngreifen()) return(SetAction("AxeStrike"));
  return(1);
  
AxeStrike:
  return(Strike());

Death:
  _inherited();
  ObjectCall(CreateObject(KT3A,0,10),"Sterb","Axt");
  RemoveObject();
  return(1);