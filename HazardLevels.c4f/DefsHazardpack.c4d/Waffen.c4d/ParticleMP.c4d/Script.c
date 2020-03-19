#strict
#include _WMM

IsWeapon:
  return(MiddleRangeWeapon());

public MinRange:
  return(50);

public MaxRange:
  return(250);

DPS:
  if(Local(0))
    return(38*5*Dmg()/(GetActMapVal("Length", "Schuss2") * GetActMapVal("Delay", "Schuss2")));
  return(38*Dmg()/(GetActMapVal("Length", "Schuss") * GetActMapVal("Delay", "Schuss")));

IsFiring:
  return(GetAction() S= "Schuss"||GetAction() S= "Schuss2"||GetAction() S= "SchussLightning");
  
Activate:
  Sound("Connect");
  Local(0)=!Local(0);
  if(Local(0))
    Sound("SpreadMode");
  else
    Sound("RapidMode");
  return(SetAction("Stop"));

GetAmmoID:
  return(ExtractAmmunition(RAM9,RAM2,LGTS,LGTR,LGTB));

GetAmmoPacketID:
  return(FindAmmoPacket(_AP7,RAP1,_CEL,_LGP,_AP0));

GetAmmoNumber:
  return(CreateAmmo(50,50,40,40,40));

SelectionSound:
  Sound("Charge3");
  return(1);

ShotSound:
  return(1);

HasLightningAmmo:
  var obj = Contents();
  if(Par(0)) obj = Par(0);
  if(GetID(obj)==LGTS)
    return(1);
  if(GetID(obj)==LGTR)
    return(1);
  if(GetID(obj)==LGTB)
    return(1);
  return(0);
  
Shot:
  // Ammo abfeuern
  if(Local(0)) {
	if(HasLightningAmmo())
      Sound("lightningLaser");
	else
	  Sound("PGFire");
    ShotExit(-20);
	ShotExit(-10);
	ShotExit(1);
	ShotExit(10);
	ShotExit(20);
  } else {
    Exit(Par(0), Par(1)*28-14,-3+Random(6),0, 0,0,0 );
	if(HasLightningAmmo(Par(0))) {
	  Par(0)->Launch(GetX()+Par(1)*20-10,GetY()-1,(1-Par(1))*1800);
	  CastParticles ("LightningSpark",1,1, Par(1)*20-10, -1, 50,60, RGB(0,100,240), RGB(0,120,255));
	} else
      ObjectCall(Par(0),"Launch",Par(1),this());
  }
  
  return(1);
  
ShotExit:
  SetVar(0,Contained());
  SetVar(1,Contents());
  SetVar(2,GetDir(Var(0)));
  if(!Var(1))
    return(1);
  SetOwner(GetOwner(Var(0)),Var(1)); 
  Exit(Var(1), Var(2)*28-14,-3+Random(6),0, 0,0,0 );
  if(HasLightningAmmo(Var(1))) {
  	Var(1)->Launch(GetX()+Var(2)*20-10,GetY()-1,(1-Var(2))*1800+Par(0)*8);
	CastParticles ("LightningSpark",1,1, Var(2)*20-10, -1, 50,60, RGB(0,100,240), RGB(0,120,255));
  } else
    ObjectCall(Var(1),"Launch",Var(2),this(),Par(0));
  return(1);

Fire:
  // Bereits beim flamen
  if (SEqual(GetAction(),"Schuss")) return(SetAction("Stop"));
  if (SEqual(GetAction(),"SchussLightning")) return(SetAction("Stop"));
  if (SEqual(GetAction(),"Schuss2")) return(SetAction("Stop"));
  // Ammo suchen
  if (!SetVar(1,Contents())) return(CheckForAmmo());
  // Flamen
  if(ActIdle()) {
    if(Local(0))
      return(SetAction("Schuss2"));
	if(HasLightningAmmo(Var(1)))
	  return(SetAction("SchussLightning"));
    return(SetAction("Schuss"));
  }
  return(1);

Schuss:
  // Träger
  SetVar(0,Contained());
  if(Contents(0,Contained())!=this()) return(SetAction("Stop"));
  if(Not(ObjectCall(Var(0),"ReadyToFire"))) return(SetAction("Stop"));
  if(Contained(Var(0))) return(SetAction("Stop"));
  if(!SetVar(1,Contents())) And(SetAction("Stop"),return(Sound("NoAmmo")));
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