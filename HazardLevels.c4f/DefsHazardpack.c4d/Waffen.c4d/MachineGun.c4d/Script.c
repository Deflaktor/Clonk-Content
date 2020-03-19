#strict
#include _WMM

IsWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon()|LongRangeWeapon());

public MinRange:
  return(5);

public MaxRange:
  return(400);

DPS:
  if(Local(0))
    return(38*Dmg()/(GetActMapVal("Length", "Schuss2") * GetActMapVal("Delay", "Schuss2")));
  return(38*Dmg()/(GetActMapVal("Length", "Schuss") * GetActMapVal("Delay", "Schuss")));

IsFiring:
  return(GetAction() S= "Schuss"||GetAction() S= "Schuss2");
  
Activate:
  Sound("Connect");
  Local(0)=!Local(0);
  if(Local(0))
    Sound("MachineStart");
  else
    Sound("MiniEnd");
  return(SetAction("Stop"));

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
  Sound("Charge3");
  return(1);

ShotSound:
  return(1);

Fire:
  // Bereits beim flamen
  if (SEqual(GetAction(),"Schuss")) return(SetAction("Stop"));
  if (SEqual(GetAction(),"Schuss2")) return(SetAction("Stop"));
  // Ammo suchen
  if (!SetVar(1,Contents())) return(CheckForAmmo());
  // Flamen
  if(ActIdle()) {
    if(Local(0))
      return(SetAction("Schuss2"));
    return(SetAction("Schuss"));
  }
  return(1);
Shot:
  // Ammo abfeuern
  if(Local(0)) {
    Exit(Par(0), Par(1)*36-18-3+Random(6),0,0, 0,0,0 );
    ObjectCall(Par(0),"Launch",Par(1),this(),Random(100)-50);
  } else {
    Exit(Par(0), Par(1)*36-18,-3+Random(6),0, 0,0,0 );
    ObjectCall(Par(0),"Launch",Par(1),this(),Random(4)-2);
  }
  ObjectCall(CreateObject(_MFL,Sum(-13,Mul(Par(1),29)),4),"Start",Contained());
  ObjectCall(CreateObject(WAPH,Sum(-5,Mul(Par(1),10))),"Start",Par(1));	
  return(1);

Schuss:
  // Träger
  SetVar(0,Contained());
  if(Contents(0,Contained())!=this()) return(SetAction("Stop"));
  if(Not(ObjectCall(Var(0),"ReadyToFire"))) return(SetAction("Stop"));
  if(Contained(Var(0))) return(SetAction("Stop"));
  if(!SetVar(1,Contents())) {
    CheckForAmmo();
	if(!SetVar(1,Contents())) And(SetAction("Stop"),return(Sound("NoAmmo")));
  }
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Var(0)),Var(1)); 
  // Richtung des Trägers abfragen
  SetVar(2,GetDir(Var(0)));
  if(!Shot(Var(1), Var(2), Var(0)))
    return(1);
  // Sound
  ShotSound();
  MunUpdate(Var(0));
  return(1);
 