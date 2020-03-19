/* -- Fernsteuerung -- */
#strict
#include _WMM

local drone;
local power;

GetAmmoID:
  return(ExtractAmmunition(_CEL,_LGP,_AP0));

GetAmmoPacketID:
  return(FindAmmoPacket(_CEL,_LGP,_AP0));

GetAmmoNumber:
  return(CreateAmmo(1,1,1));

SelectionSound:
  Sound("RadioStatic");
  return(1);

public func GetPower() {
  return(power);
}

public func GetDrone() {
  return drone;
}

/* Objekt keine Waffe (auch wegen WalkArmed/Unarmed) */
IsWeapon:
  return(0);

Shot:
  // Sound
  Sound("Teleport");
  drone = FindRemoteTarget();
  if (drone) {
    Message("%s erfaßt",drone,GetName(drone));
    SetOwner(GetOwner(Par(0)),drone);
    drone->~SetPatrolObject(this());
    drone->~SetRemote(this());
    // Energiezelle verbrauchen, wenn Ziel gefunden
    if(GetID(Par(0))==_CEL) power = 0;
    if(GetID(Par(0))==_LGP) power = 1;
    if(GetID(Par(0))==_AP0) power = 2;
    RemoveObject(Par(0));
  } else {
    Message("Kein Ziel in Reichweite",Contained());
  }
return(1);

/* Feuern - Trägerbezogene Effekte lieber auf Activate */
Activate:
  // Aktuelle Drone steuern
  if (drone) {
    CreateMenu(GetID(),Par(0),this());
    if(drone->~GetPatrolObject() != this())
      AddMenuItem("Auto-Pilot","AutoPilot",GetID(drone),Par(0));
    else 
      AddMenuItem("Manuell steuern","AutoPilot",GetID(Par(0)),Par(0));
    AddMenuItem("Freigeben","Freigabe",MI_P,Par(0));
    return(1);
  }
  Fire();
  return(1);


protected func Freigabe() {
  SetOwner(-1,drone);
  drone->~SetPatrolObject();
  drone->~SetRemote();
  drone=0;
  power=0;
  Message("Ziel freigegeben",Contained());
  return(1);
}

protected func AutoPilot() {
  Sound("Click");
  if(drone->~GetPatrolObject() != this())
    drone->~SetPatrolObject(this());
  else
    drone->~SetPatrolObject();
  return(1);
}

private FindRemoteTarget:
  while (SetVar(0,FindObject(0,0,0,-1,-1,0,0,0,NoContainer(),Var(0))))
    if (LessThan(Distance(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))),250))
    if (ObjectCall(Var(0),"RemoteControlAccess",this()))
      return(Var(0));
  return(0);

/* Steuerung (Rückgabewert 1 bei aktivem Ziel) */

public ControlUp:
  if (Not(drone)) return(0);
  if(drone->~GetPatrolObject() == this()) return(0);
  Sound("Click");
  ObjectCall( drone,"ControlUp",Par(0) );
  ObjectCall( drone,"ControlUpSingle",Par(0) );
  SetPlrView(GetOwner(Par(0)),drone);
  SetComDir(COMD_None(), Par(0));
  return(1);

public ControlDown:
  if (Not(drone)) return(0);
  if(drone->~GetPatrolObject() == this()) return(0);
  Sound("Click");
  ObjectCall( drone,"ControlDown",Par(0) );
  ObjectCall( drone,"ControlDownSingle",Par(0) );
  SetPlrView(GetOwner(Par(0)),drone);
  SetComDir(COMD_None(), Par(0));
  return(1);

public ControlLeft:
  if (Not(drone)) return(0);
  if(drone->~GetPatrolObject() == this()) return(0);
  Sound("Click");
  ObjectCall( drone,"ControlLeft",Par(0) );
  ObjectCall( drone,"ControlLeftSingle",Par(0) );
  SetPlrView(GetOwner(Par(0)),drone);
  SetComDir(COMD_None(), Par(0));
  return(1);

public ControlRight:
  if (Not(drone)) return(0);
  if(drone->~GetPatrolObject() == this()) return(0);
  Sound("Click");
  ObjectCall( drone,"ControlRight",Par(0) );
  ObjectCall( drone,"ControlRightSingle",Par(0) );
  SetPlrView(GetOwner(Par(0)),drone);
  SetComDir(COMD_None(), Par(0));
  return(1);
