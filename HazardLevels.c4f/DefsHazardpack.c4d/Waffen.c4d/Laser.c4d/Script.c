#strict
#include _WOM

Dmg:
  return(DefinitionCall(GetAmmoID(), "Dmg", DeathLaser()));

IsWeapon:
  return(ShortRangeWeapon());

public MinRange:
  return(0);

public MaxRange:
  return(100);
  
Activate:
  if(!ActIdle())
    return(1);
  Sound("Connect");
  ChangeDef(HLD_);
  ShiftContents(Contained(), 0, HLD_);
  return(1);

SelectionSound:
  Sound("ChargeRay");
  return(1);

ShotSound:
  //Sound("Ray");
  return(1);
  
/* Ammo ID */  
GetAmmoID:
  return(_LSR);

Shot:
  var obj;
  var dist = 100;
  // Gegnerische Clonks/Aliens/Wachdronen suchen
  while(SetVar(0,FindObject(0,-100,-100,200,200,OCF_Prey(),0,0,NoContainer(),Var(0)))) {
      // Gehört nicht dem Spieler
      if(Contained()->GetTarget(Var(0)) && Var(0)!=Contained() )
        // Lebt noch
        if(GetAlive(Var(0)))
          if(Var(1)=Distance(GetX(),GetY(),GetX(Var(0)),GetY(Var(0))) < dist)
            // Weg Frei
            if(PathFree(GetX(),GetY(),GetX(Var(0)),GetY(Var(0)))) {
              obj=Var(0);
              dist=Var(1);
            }
  }
  if(obj)
    Zap(obj);
  return(0);

Zap:
  ObjectCall(CreateObject(GetAmmoID(),0,0,-1), "Launch",this(),Par(0), DeathLaser());
  return(1);
  
DeathLaser:
  return(0);