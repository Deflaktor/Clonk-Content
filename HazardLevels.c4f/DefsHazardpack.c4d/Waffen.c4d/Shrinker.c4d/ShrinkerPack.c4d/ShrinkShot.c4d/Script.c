#strict
#include _POV

/* Wird abgefeuert, Par(0) ist Schußrichtung */
public func Launch(int dir) {
  if (dir==DIR_Left()) SetLocal(0,-80);
  if (dir==DIR_Right()) SetLocal(0,+80);
  SetAction("Travel");
}
  
/* Fliegt */
protected func Travel() {
  // Treffer-Überprüfung
  var obj;
  if(obj=CheckHit(-10,-8,20,20))
    return(HitObject(obj));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
}

public func HitObject(object obj) {
  ObjectCall(obj,"Shrink",GetOwner());
  Hit();
}
  
/* Treffer */
public func Hit() {
  RemoveObject();
}