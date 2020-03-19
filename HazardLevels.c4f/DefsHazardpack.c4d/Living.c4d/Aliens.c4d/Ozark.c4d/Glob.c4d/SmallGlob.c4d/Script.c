/* Small Glob */

#strict
#include _POV

public func IsProjectile() {
  return(1);
}

local timer;

/* Timer */
protected func Decay() {
  timer++;
  if (timer > Random(5)) RemoveObject();
}
  
/* Fliegt */
protected func Travel() {
  var obj;
  if(obj=CheckHit(-5,-5,10,10))
    Hit();
}
  
/* Treffer */
protected func Hit() {
  RemoveObject();
}
