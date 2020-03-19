#strict
#include _WMM

IsWeapon:
  return(MiddleRangeWeapon()|LongRangeWeapon());

GetAmmoID:
  return(ExtractAmmunition(_AM6,_AM6));

GetAmmoPacketID:
  return(FindAmmoPacket(_AP6,_PP6));

public MinRange:
  return(25);

public MaxRange:
  return(400);

GetAmmoNumber:
  return(CreateAmmo(25,125));

IsFiring:
  return(GetAction() S= "Schuss");
  
SelectionSound:
  Sound("MachineStart");
  return(1);

ShotSound:
  return(1);

Fire:
  // Bereits beim Schieﬂen
  if (SEqual(GetAction(),"Schuss")) return(SetAction("Auslaufen"));
  // Ammo suchen
  if (!SetVar(1,Contents())) return(CheckForAmmo());
  // Flamen
  if(ActIdle())
    SetAction("Warmlaufen");
  return(1);

Shot:
  // Ammo abfeuern
  Exit(Par(0), Par(1)*36-18,-3+Random(6),0, 0,0,0 );
  ObjectCall(Par(0),"Launch",Par(1),this(),Random(6)-3);
  ObjectCall(CreateObject(WAMF,Sum(-13,Mul(Par(1),29)),4),"Start",Par(1));
  ObjectCall(CreateObject(WAPH,Sum(-5,Mul(Par(1),10))),"Start",Par(1));	
  return(1);

Schuss:
  // Tr‰ger
  SetVar(0,Contained());
  if(Contents(0,Contained())!=this()) return(SetAction("Stop"));
  if(Not(ObjectCall(Var(0),"ReadyToFire"))) return(SetAction("Stop"));
  if (Contained(Var(0))) return(SetAction("Stop"));
  if (!SetVar(1,Contents())) And(SetAction("Auslaufen"),return(Sound("NoAmmo")));  
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Var(0)),Var(1)); 
  // Richtung des Tr‰gers abfragen
  SetVar(2,GetDir(Var(0)));
  if(!Shot(Var(1), Var(2), Var(0)))
    return(1);
  MunUpdate(Var(0));
  return(1);

MunUpdate:
  if(Local(9)==25)
    SetLocal(9,125);
  return(inherited(Par(0),Par(1),Par(2)));
