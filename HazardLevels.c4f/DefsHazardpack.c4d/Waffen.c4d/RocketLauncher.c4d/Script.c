/*-- RocketLauncher --*/

#strict
#include _WMM

IsWeapon:
  return(MiddleRangeWeapon()|LongRangeWeapon());

public MinRange:
  return(50);

public MaxRange:
  return(400);

GetAmmoID:
  return(ExtractAmmunition(_ARS,_HMS,_AM2,_SM4,_RM2,_SM2));

GetAmmoPacketID:
  return(FindAmmoPacket(_ARP,_HMP,_AP2,_SR4,_RP2,_SR2));

GetAmmoNumber:
  return(CreateAmmo(3,7,10,5,7,4));

SelectionSound:
  Sound("Charge4");
  return(1);

ShotSound:
  Sound("Launch");
  return(1);

/* Spezialsteuerung durch Träger */
ControlThrow:  
  if(GetAction(Par(0)) S= "Push") return(0);
  // Träger hat gezielt
  if (SEqual( GetAction(Par(0)),"AimRocket" )) return(1,Fire());  
  // Träger nicht bereit zum neuen Zielen
  if (Not(ObjectCall( Par(0), "ReadyToAim" ))) return(1);
  // Träger neue Zielaktion setzen
  if (And( ObjectSetAction(Par(0),"AimRocket"), SetPhase(4,Par(0)) )) return(1);      
  return(0);

ControlUp:
  // Träger Zielaktion
  if (SEqual(GetAction(Par(0)),"AimRocket"))
    if (GreaterThan(GetPhase(Par(0)),0))
      return(SetPhase( Sum(GetPhase(Par(0)),-1), Par(0) ));
  // Keine Spezialsteuerung
  return(0);

ControlDown:
  // Träger Zielaktion
  if (SEqual(GetAction(Par(0)),"AimRocket"))
    if (LessThan(GetPhase(Par(0)),6))
      return(SetPhase( Sum(GetPhase(Par(0)),+1), Par(0) ));
  // Keine Spezialsteuerung
  return(0);

ControlLeft:
  // Träger Zielaktion
  if (SEqual(GetAction(Par(0)),"AimRocket"))
    return(SetDir(DIR_Left(),Par(0)));
  // Keine Spezialsteuerung
  return(0);

ControlRight:
  // Träger Zielaktion
  if (SEqual(GetAction(Par(0)),"AimRocket"))
    return(SetDir(DIR_Right(),Par(0)));
  // Keine Spezialsteuerung
  return(0);

ControlRightDouble:
  // Zielaktion abbrechen
  if (IsAiming())
    And( ObjectCall( Par(0), "StopAiming" ), SetComDir(COMD_Right(),Par(0)) );
  // Keine Spezialsteuerung
  return(0);

ControlLeftDouble:
  // Zielaktion abbrechen
  if (IsAiming())
    And( ObjectCall( Par(0), "StopAiming" ), SetComDir(COMD_Left(),Par(0)) );
  // Keine Spezialsteuerung
  return(0);
  
/* Wird gerade vom Träger gezielt? */
IsAiming:
  return (SEqual( GetAction(Contained()),"AimRocket" ));

Shot:
  // Richtung des Projektils berechnen
	// X-Austritt  
  SetVar(4,Mul(Par(3),4));
  if (GreaterThan(Par(3),4)) SetVar(4,Mul(Sub(8,Par(3)),4));
  if ( Equal(Par(1),DIR_Left()) ) SetVar(4, Mul(Var(4),-1) );
  // Y-Austritt
  SetVar(5,Mul(Sum(Par(3),-4),6));
  // R-Austritt
  SetVar(7, Mul( Par(3), 22) );  
  if ( Equal(Par(1),DIR_Left()) ) SetVar(7, Mul(Var(7),-1) );
  // XDir
  SetVar(3, Var(4)* 10 );
  // YDir
  SetVar(2, (Par(3)-4)* 30 );
	// RDir
  SetVar(6, 0);
  
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Par(2)),Par(0)); 
  // Ammo abfeuern
  Exit(Par(0), Var(4),Var(5),Var(7), Var(3),Var(2),Var(6) );
  ObjectCall(Par(0),"Launch",Var(3),Var(2));
  return(1);