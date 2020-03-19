/* Glob */

#strict
#include _POV

public func IsProjectile() {
  return(1);
}

/* Wird abgefeuert */
public func Launch() {
  SetAction("Travel");
}
  
/* Fliegt */
protected func Travel() {
  // Treffer-Überprüfung
  var obj;
  if(Random(2))
    if(obj=CheckHit(-5,-5,10,10))
      HitObject(obj);
}

private func HitObject(object obj) {
  DoEnergy(-4*GetCon()/100, Par(0));
  Hit();
}

/* Treffer */
protected func Hit() {
  BlastObjects(GetX(),GetY(),1*GetCon()/20);
  Sound("OzarkGlob*");
  if(Random(100)<=GetCon())
    SetVar(0,CreateObject(GLB2));
  SetYDir(-35+Random(70),Var());
  SetXDir(-35+Random(70),Var());
  SetCon(GetCon(),Var(0));
  RemoveObject();
  return(1);
}