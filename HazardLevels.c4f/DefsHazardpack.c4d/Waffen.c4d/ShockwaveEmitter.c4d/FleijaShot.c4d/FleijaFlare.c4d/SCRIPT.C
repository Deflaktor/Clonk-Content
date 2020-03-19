#strict

static fleijaFlareSizes;

local growTime, shrinkTime;

protected func Launch() {
  if(!fleijaFlareSizes)
    fleijaFlareSizes = [2,3,5,9,12,16,20,23,24,25];
  growTime = 10;
  shrinkTime = growTime;
  Sound("FleijaFlare");
  SetAction("Shockwave");
  SetCategory(C4D_Foreground);
  return(1);
}

public func DestroyMaterials() {
  return(0);
}

private func GetFrame(int frame, int maxFrame) {
  return(BoundBy(frame*GetLength(fleijaFlareSizes)/maxFrame, 0, GetLength(fleijaFlareSizes)-1));
}

private func GetFrameInverse(int frame, int maxFrame) {
  return(BoundBy((maxFrame-frame)*GetLength(fleijaFlareSizes)/maxFrame, 0, GetLength(fleijaFlareSizes)-1));
}

protected func ResizeGrow() {
  var target = fleijaFlareSizes[GetFrame(GetActTime(),growTime)]*2;
  var current = GetCon();
  DoCon(target - current);
  SetR(GetR()+10);
  if(GetActTime()>=growTime)
    SetAction("ShockwaveShrink");
  return(1);
}

protected func ResizeShrink() {
  var target = fleijaFlareSizes[GetFrameInverse(GetActTime(),shrinkTime)]*2;
  var current = GetCon();
  DoCon(target - current);
  SetR(GetR()+10);
  if(GetActTime()>=shrinkTime)
    Remove();
  return(1);
}

protected func Remove() {
  CreateObject(_FLB,0,0,GetOwner())->Launch();
  RemoveObject();
  return(1);
}
