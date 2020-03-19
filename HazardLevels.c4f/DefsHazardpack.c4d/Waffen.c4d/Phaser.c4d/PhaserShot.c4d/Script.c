/*-- Phaserschuß --*/
#strict
#include _POV
// Local 0: Fluggeschwindigkeit horizontal
local power;

Dmg: return(5+Par(0));

/* Wird abgefeuert, Par(0) ist Schußrichtung */
public Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-100);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+100);
  power = Par(1);
  DoCon(power*12);
  SetAction("Travel");
  PhaserSetColorByPower(power, this());
  return(1);
  
/* Fliegt */
private Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-5,-5,10,10))
    return(HitObject(Var(0)));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
  SetLocal(5,GetColorDw());
  CreateParticle("PxSpark", 0, 0, 0, 0,15+power*3,GetColorDw());
  PhaserSetColorByPower(power, this());
  //SetVar(2,Random(360));
  //LaunchLightning(GetX(),GetY(),Sin(Var(2),15),20,Cos(Var(2),15),20);
  return(1);
  
/* Treffer */
protected Hit:
  ObjectCall(CreateObject(EXPL),"Launch",5+power);
  RemoveObject();
  return(1);
    
private HitObject: // C4Object* pObject
  if(GetAction(Par(0)) eq "Frozen")
    ObjectSetAction(Par(0),"Walk");
  Sound("ProjectileHit*");
  var damage = Dmg(power);
  if(GetID(Par(0))==_FBL)
    damage = damage*10/3;
  DoEnergy(-damage,Par(0));
  DoDamage(damage,Par(0));
  SetXDir(GetXDir(Par(0))+Local(0)/4+Local(0)*power/24,Par(0));
  RemoveObject();
  return(1);