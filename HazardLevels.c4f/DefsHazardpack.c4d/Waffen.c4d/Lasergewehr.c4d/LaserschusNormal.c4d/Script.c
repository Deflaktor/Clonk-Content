/*-- Laser --*/

#strict
#include _POV

// Local 0: XDir
// Local 1: YDir

/* Wird abgefeuert */
public Launch:  
  // Schußrichtung
  Local(2)=25;
  SetLocal(0,Par(0));
  SetLocal(1,Par(1));
  SetPosition(GetX()+Local(0)/10,GetY()+Local(1)/10);
  SetAction("Travel");
  // Sicht verfolgen
  SetPlrView(GetOwner(),this());
  return(1);
  
/* Fliegt */
private Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-20,-20,40,40))
    if(GetID(Var(0))!=ST5B)
      return(HitObject(Var(0)));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  Local(2)--;
  if(Local(2)<1)
    Hit();
  Explosion();
  return(1);
  
Explosion:
  ObjectCall(CreateObject(EXPL, Par(0), Par(1)),"Launch",Local(2)/2);
  return(1);

private func HitObject(object obj) {
  DoDamage(Dmg()/5,obj);
  DoEnergy(-Dmg()/5,obj);
  Hit();
  return(1);
}

/* Treffer */
public Hit:
  ObjectCall(CreateObject(EXPL),"Launch", Dmg()+5);
  RemoveObject();
  return(1);

/* Eintritt */
protected Entrance:
  if (Equal(GetAction(),"Travel")) Hit();
  return();
  
Dmg: return(20);