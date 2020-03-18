#strict
#appendto FXQ1

public func Activate(int _iLevel) {
  iLevel=_iLevel;
  if(!iLevel) iLevel=100+Random(101);
  iLifeTime=iLevel/2;
  SetAction("Quake");
  return(1);
}


global func ShakeViewPort(int iLevel, object pObj, int iOffX, int iOffY) {
  if(iLevel <= 0) return(false);
}
