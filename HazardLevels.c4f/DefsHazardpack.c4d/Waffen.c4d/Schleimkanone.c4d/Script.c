#strict
#include _WMM

IsWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon());

public MinRange:
  return(50);

public MaxRange:
  return(200);
  
GetAmmoID:
  return(ExtractAmmunition(SH10,SH11));

GetAmmoPacketID:
  return(FindAmmoPacket(RAP1,_AP7));

GetAmmoNumber:
  return(CreateAmmo(40,40));

SelectionSound:
  Sound("gelselect");
  return(1);

ShotSound:
  Sound("gelshot");
  return(1);

Shot:
  Exit(Par(0), Sum(-10,Mul(Par(1),20)),0,0, Sum(-3,Mul(Par(1),6)),-3+Random(2),0 );
  ObjectCall(Par(0),"Launch");
  return(1);
