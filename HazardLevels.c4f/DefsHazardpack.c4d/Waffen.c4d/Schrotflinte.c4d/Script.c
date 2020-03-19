/*-- Phaser2 --*/

#strict
#include _WMM

IsWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon());

public MinRange:
  return(10);

public MaxRange:
  return(200);

DPS:
  return(38*Dmg()/(GetActMapVal("Length", "Reload") * GetActMapVal("Delay", "Reload")));
  
DPA:
  return(Local(9)*Dmg()/25);
  
Dmg:
  return(_inherited()*25);
  
IsWeapon:
  return(ShortRangeWeapon());

GetAmmoID:
  return(ExtractAmmunition(_AM6));

GetAmmoPacketID:
  return(FindAmmoPacket(_AP6));

GetAmmoNumber:
  return(CreateAmmo(25));

ExtractAmmoPacket:
  var inherit = inherited();
  var obj;
  var carrier = Contained();
  if(carrier) 
    if(obj=FindObject(_PP6,-5,-5,10,10,0,0,0,NoContainer())) {
      Enter(carrier, obj);
      obj->Activate();
      return(inherited());
    }
  return(inherit);

SelectionSound:
  Sound("ShotgunReload");
  return(1);

ShotSound:
  Sound("Shotgun");
  return(1);

Shot:
  // Ammo abfeuern
  Exit(Par(0), Par(1)*36-18-3+Random(6),-3+Random(6),0, 0,0,0 );
  ObjectCall(Par(0),"Launch",Par(1),this(),Random(120)-60);
  ObjectCall(CreateObject(WAPH,Sum(-5,Mul(Par(1),10))),"Start",Par(1));	
  ObjectCall(CreateObject(WAMF,Sum(-13,Mul(Par(1),29)),4),"Start",Par(1));
  return(1);

Fire:
  // Noch beim Nachladen
  if (SEqual(GetAction(),"Reload")) return(0);
  // Träger
  SetVar(0,Contained());
  for(var i=1;i<=25;i++) {
    // Ammo suchen
    if (!SetVar(1,Contents())) {
      if(CheckForAmmo())
      CheckForAmmo();
      return(0);
    }
    // Besitzer des Projektils setzen
    SetOwner(GetOwner(Var(0)),Var(1)); 
    // Richtung des Trägers abfragen
    SetVar(2,GetDir(Var(0)));
    SetVar(3,GetPhase(Var(0)));
    if(!Shot(Var(1), Var(2), Var(0), Var(3)))
      return(1);
  }
  // Sound
  ShotSound();
  // Nachladen
  SetAction("Reload");
  MunUpdate(Var(0));
  return(1);

MunUpdate:
  if(Local(9)==25)
    SetLocal(9,50);
  return(inherited(Par(0),Par(1),Par(2)));