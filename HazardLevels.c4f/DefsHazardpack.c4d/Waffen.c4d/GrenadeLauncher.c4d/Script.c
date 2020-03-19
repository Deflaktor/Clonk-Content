/*-- GrenadeLauncher --*/

#strict
#include _WMM

// Local 0 Timer

Initialize:
  SetLocal(0,0);
  return(1);

GetAmmoID:
  return(ExtractAmmunition(_CGM,_AM5,_CGM,_AM5));

GetAmmoPacketID:
  return(FindAmmoPacket(_CGP,_AP5,_CGM,_AM5));

GetAmmoNumber:
  return(CreateAmmo(5,5,1,1));

SelectionSound:
  Sound("Buckle3");
  return(1);

ShotSound:
  Sound("Mortar");
  return(1);

/* Aktivierung */
Activate:
  Sound("Bip");
  // Aktivator wird Besitzer
  SetOwner( GetOwner(Par(0)) );
  // Timer erhöhen
  SetLocal(0, Sum(Local(0),+1) );
  if (GreaterThan( Local(0), 5 )) SetLocal(0,0);
  if(Local(0)==0)
    Message("Explosion bei Aufprall",Par(0));
  else
    Message("0%d",Par(0),Local(0));  
  return(1);

/* Spezialsteuerung durch Träger */
ControlThrow:  
  if(GetAction(Par(0)) S= "Push") return(0);
  // Träger hat gezielt
  if (SEqual( GetAction(Par(0)),"AimGrenade" ))
    return(1,Fire());
  // Träger nicht bereit zum neuen Zielen
  if (Not(ObjectCall( Par(0), "ReadyToAim" ))) return(1);
  // Träger neue Zielaktion setzen
  if (And( ObjectSetAction(Par(0),"AimGrenade"), SetPhase(4,Par(0)) )) 
    return(1);
  return(0);

ControlUp:
  // Träger Zielaktion
  if (SEqual(GetAction(Par(0)),"AimGrenade"))
    if (GreaterThan(GetPhase(Par(0)),0))
      return(SetPhase( Sum(GetPhase(Par(0)),-1), Par(0) ));
  // Keine Spezialsteuerung
  return(0);

ControlDown:
  // Träger Zielaktion
  if (SEqual(GetAction(Par(0)),"AimGrenade"))
    if (LessThan(GetPhase(Par(0)),6))
      return(SetPhase( Sum(GetPhase(Par(0)),+1), Par(0) ));
  // Keine Spezialsteuerung
  return(0);

ControlLeft:
  // Träger Zielaktion
  if (SEqual(GetAction(Par(0)),"AimGrenade"))
    return(SetDir(DIR_Left(),Par(0)));
  // Keine Spezialsteuerung
  return(0);

ControlRight:
  // Träger Zielaktion
  if (SEqual(GetAction(Par(0)),"AimGrenade"))
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

ControlDig:  
  // Zielaktion Timer setzen
  if (IsAiming())
    return(Activate(Par(0)));
  // Keine Spezialsteuerung
  return(0);
  
/* Wird gerade vom Träger gezielt? */
IsAiming:
  return (SEqual( GetAction(Contained()),"AimGrenade" ));

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
  SetVar(3, Mul( Var(4), 1) );
  // YDir
  SetVar(2, Mul( Sum(Par(3),-4), 3) );
	// RDir
  SetVar(6, 20);
  
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Par(2)),Par(0)); 
  // Ammo abfeuern
  Exit(Par(0), Var(4),Var(5),Var(7), Var(3),Var(2),Var(6) );
  ObjectCall(Par(0),"Launch",Local(0));
  return(1);


MunUpdate:
  if(Local(9)==1)
    SetLocal(9,10);
  return(inherited(Par(0),Par(1),Par(2)));
