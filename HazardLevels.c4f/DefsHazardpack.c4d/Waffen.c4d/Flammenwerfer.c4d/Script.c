#strict
#include _WMM

GetAmmoID:
  return(ExtractAmmunition(_AM3));

GetAmmoPacketID:
  return(FindAmmoPacket(_AP3));

GetAmmoNumber:
  return(CreateAmmo(100));

SelectionSound:
  Sound("Charge2");
  return(1);

ShotSound:
  return(1);
  
IsFiring:
  return(GetAction() S= "Schuss");
  
IsWeapon:
  return(ShortRangeWeapon());

public MinRange:
  return(50);

public MaxRange:
  return(100);

ControlUp:
  // Träger Zielaktion
  if(Local(0)<6)
    return(0);
  if (!(GetAction(Par(0))S="Jump"||GetAction(Par(0))S="ArmedJump"))
    return(0);
  if(GetPhase(Par(0))<2)
    return(0);
  if (!SetVar(1,Contents())) {
    Sound("NoAmmo");
	return(0);
  }
  SetYDir(-10,Par(0));
  for(var i=0;i<10;i++) {
    SetVar(1,Contents());
	if(!Var(1))
	  break;
    SetOwner(GetOwner(Par(0)),Var(1)); 
    if(!ShotRunter(Var(1)))
      break;
	SetYDir(GetYDir(Par(0))-4,Par(0));
	SetXDir(GetXDir(Par(0))+GetDir(Par(0))*2-1,Par(0));
  }
  Sound("FireJump");
  MunUpdate(Par(0));
  Local(0)=0;
  // Keine Spezialsteuerung
  return(1);

Timer:
  Local(0)++;
  return(_inherited());
  
ShotRunter:
  // Ammo abfeuern
  Exit(Par(0), 0,12,0, 0,0,0 );
  ObjectCall(Par(0),"Launch",0,this(),1);
  return(1);
  
Shot:
  // Ammo abfeuern
  Exit(Par(0), Par(1)*26-13,0,0, 0,0,0 );
  ObjectCall(Par(0),"Launch",Par(1),this(),0);
  return(1);
  
Fire:
  // Bereits beim flamen
  if (SEqual(GetAction(),"Schuss")) return(SetAction("Stop"));
  // Ammo suchen
  if (!SetVar(1,Contents())) return(CheckForAmmo());
  // Flamen
  if(ActIdle())
    SetAction("Schuss");
  return(1);

Schuss:
  // Träger
  SetVar(0,Contained());
  if(Not(ObjectCall(Var(0),"ReadyToFire"))) return(SetAction("Stop"));
  if(Contained(Var(0))) return(SetAction("Stop"));
  if(!SetVar(1,Contents())) And(SetAction("Stop"),return(Sound("NoAmmo")));
  // Besitzer des Projektils setzen
  SetOwner(GetOwner(Var(0)),Var(1)); 
  // Richtung des Trägers abfragen
  SetVar(2,GetDir(Var(0)));
  if(!Shot(Var(1), Var(2)))
    return(1);
  // Sound
  ShotSound();
  MunUpdate(Var(0));
  return(1);
