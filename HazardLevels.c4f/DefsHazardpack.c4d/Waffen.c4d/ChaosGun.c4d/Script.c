#strict
#include _WMM

GetAmmoID:
  return(ExtractAmmunition(_AM7,_AMC));

GetAmmoPacketID:
  return(FindAmmoPacket(_AP7,RAP1));

GetAmmoNumber:
  return(CreateAmmo(30,6));
  
GetSpecialShotID:
  if(Local(8)==_AM7)
    return(AM79);
  if(Local(8)==_AMC)
    return(AMC2);
  return(0);
  
public IsWeapon:
  return(ShortRangeWeapon());

public MinRange:
  return(5);

public MaxRange:
  return(100);
  
GetSpecialShotCost:
  if(Local(8)==_AM7)
    return(10);
  if(Local(8)==_AMC)
    return(3);
  return(999999);
  
SpecialShotSound:
  if(Local(8)==_AM7)
    Sound("puff");
  if(Local(8)==_AMC)
    Sound("Gasy");
  return(1);

SelectionSound:
  Sound("Chaos");
  return(1);

ShotSound:
  Sound("Shot1");
  return(1);
   
Activate:
  // Noch beim Nachladen
  if (SEqual(GetAction(),"Reload")) return(0);
  // Träger
  SetVar(0,Contained());
  // Ammo suchen
  if (!Contents()) return(CheckForAmmo());
  if (ContentsCount()<GetSpecialShotCost()) return(Sound("NoAmmo"));
  Var(1)=ContentsCount()-GetSpecialShotCost();
  while(ContentsCount()>Var(1))
    RemoveObject(Contents());
  SetVar(1,CreateContents(GetSpecialShotID()));
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Var(0)),Var(1)); 
  // Richtung des Trägers abfragen
  SetVar(2,GetDir(Var(0)));
  SetVar(3,GetPhase(Var(0)));
  if(!Shot(Var(1), Var(2), Var(0), Var(3)))
    return(1);
  // Sound
  SpecialShotSound();
  ShotSound();
  // Nachladen
  SetAction("Reload");
  MunUpdate(Var(0));
  return(1);
  
Shot:
  // Ammo abfeuern
  Exit(Par(0), Par(1)*26-13,0,0, 0,0,0 );
  ObjectCall(Par(0),"Launch",Par(1),this());
  return(1);
