/*-- Projectile Template --*/

#strict

local xSpeed, ySpeed;

public func IsProjectile() {
  return(1);
}
  
public func Dmg() {
  return(0);
}

public func GetFixedHorizontalSpeed() {
  return xSpeed;
}

public func GetFixedVerticalSpeed() {
  return ySpeed;
}

public func SetFixedHorizontalSpeed(int speed) {
  xSpeed = speed;
}

public func SetFixedVerticalSpeed(int speed) {
  ySpeed = speed;
}

protected func CheckHit(int x, int y, int width, int height) {
  var obj;
  if(obj=FindObject(_ORB,x,y,width,height,0,0,0,NoContainer())) {
    obj->Damage();
    return(0);
  }
  while(obj=FindObject(0,x,y,width,height,OCF_Prey(),0,0,NoContainer(),obj))
    if(GetTarget(obj))
      return(obj);
  obj=0;
  while(obj=FindObject(0,1,0,0,0,OCF_Prey(),0,0,NoContainer(),obj))
    if(GetTarget(obj))
      return(obj);
  return(0);
}

/* Zielsuche */
protected func SearchTarget(int distance) {
  // Setze standard Suchreichweite
  if(!distance)
    distance=150;
  // Noch nicht abgefeuert
  if (Contained()) return(0);
  // Nächstgelegenes Ziel suchen
  var obj;
  if(!(obj=FindTarget(0,0,-1,-1))) return(0);
  // Ziel zu weit weg
  if (Distance(GetX(),GetY(),GetX(obj),GetY(obj)) > distance ) return(0);
  // Keine Sichtlinie
  if (!PathFree(GetX(),GetY(),GetX(obj),GetY(obj))) return(0);
  // Neues Ziel gefunden
  return(obj);
}

protected func RejectEntrance() {
  if(GetAction() S= "Travel")
    return(1);
  return(_inherited());
}