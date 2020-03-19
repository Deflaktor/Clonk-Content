#strict
#include _POV

public func Dmg() {
  return(2);
}

/* Wird abgefeuert, dir ist Schußrichtung */
public func Launch(int dir) {
  if (dir == DIR_Left()) SetLocal(0,-80);
  if (dir == DIR_Right()) SetLocal(0,+80);
  SetAction("Travel");
  SetDir(dir);
}
  
/* Fliegt */
protected func Travel() {
  // Treffer-Überprüfung
  var obj;
  if(obj=CheckHit(-7,-7,14,14))
    return(SonicHit(obj));
  // Bewegung
  SetXDir(Local(0));
  SetYDir(0);
}

/* Treffer */
protected func Hit() {
  RemoveObject();
  Sound("Thump1");
}

private func SonicHit(object obj) {
  DoEnergy(-Dmg(),obj);
  Fling(obj,Random(20)-10,-2-Random(5));
  Hit();
}