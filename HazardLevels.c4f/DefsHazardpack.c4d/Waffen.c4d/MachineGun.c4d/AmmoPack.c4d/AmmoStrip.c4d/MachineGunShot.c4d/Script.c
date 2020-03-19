/*-- Maschinengewehrkugel --*/
#strict
#include _POV

// Local 0: Fluggeschwindigkeit horizontal

/* Wird abgefeuert, Par(0) ist Schußrichtung */
public Launch:  
  if (Equal(Par(0),DIR_Left())) SetLocal(0,-200);
  if (Equal(Par(0),DIR_Right())) SetLocal(0,+200);
  SetLocal(1,Par(2));
  SetAction("Travel");
  return(1);
  
/* Fliegt */
private Travel:
  // Treffer-Überprüfung
  if(Var(0)=CheckHit(-12,-5,24,10))
    return(HitObject(Var(0)));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(Local(1));
  return(1);
  SetLocal(2,Local(2)+1);
  if(Local(2)>5)
    SetLocal(2,5);
  var i;
  for(i=0;i<Local(2);i++)
    CreateObject(_FR3,-i*Local(0)/10+5-Random(10));
  return(1);
  
/* Treffer */
protected Hit:
  ObjectCall(CreateObject(EXPL),"Launch",Dmg()+1);
  RemoveObject();
  return(1);
    
private HitObject: // C4Object* pObject
  Sound("ProjectileHit*");
  DoEnergy(-Dmg(),Par(0));
  DoDamage(Dmg()+1,Par(0));
  SetXDir(GetXDir(Par(0))+Local(0)/10,Par(0));
  if(GetXDir(Par(0))>100||GetXDir(Par(0))<-100)
    Fling(Par(0),Min(2,Max(-2,GetXDir(Par(0))+Local(0)/200)),Min(2,Max(-2,GetYDir(Par(0))-1)));
  RemoveObject();
  return(1);
  
Dmg:
  return(2);