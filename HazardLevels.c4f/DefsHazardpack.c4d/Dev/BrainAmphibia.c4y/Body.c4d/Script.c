/*-- Brain Amphibia --*/

#strict
#include _KI_
#include _YBA

local pHead, pNeck, pUpperLeftArm, pUpperRightArm, pLeftEllbow, pRightEllbow, pLeftHand, pRightHand, pLeftThigh, pRightThigh, pLeftKnee, pRightKnee, pLeftLeg, pRightLeg, pLeftFoot, pRightFoot;
local aHead, aLeftArm, aRightArm, aLeftHand, aRightHand, aLeftLeg, aRightLeg;

func Initialize() {
  return(_inherited());
}

func Init() {
  var darkColor = RGB(150,150,150);
  pHead = CreateObject(_YBH,0,0,GetOwner());
  pNeck = CreateObject(_YBN,0,0,GetOwner());
  pLeftThigh = CreateObject(_YBT,0,0,GetOwner());
  pLeftLeg = CreateObject(_YBL,0,0,GetOwner());
  pLeftKnee = CreateObject(_YBK,0,0,GetOwner());
  pLeftFoot = CreateObject(_YBF,0,0,GetOwner());
  pRightThigh = CreateObject(_YBT,0,0,GetOwner());
  SetClrModulation(darkColor, pRightThigh);
  pRightLeg = CreateObject(_YBL,0,0,GetOwner());
  SetClrModulation(darkColor, pRightLeg);
  pRightKnee = CreateObject(_YBK,0,0,GetOwner());
  SetClrModulation(darkColor, pRightKnee);
  pRightFoot = CreateObject(_YBF,0,0,GetOwner());
  SetClrModulation(darkColor, pRightFoot);
  SetObjectOrder(pNeck, pHead, 1);
  SetObjectOrder(this(), pNeck, 1);
  SetObjectOrder(pRightThigh, pNeck, 1);
  SetObjectOrder(pRightLeg, pRightThigh, 1);
  SetObjectOrder(pRightFoot, pRightLeg, 1);
  SetObjectOrder(pRightKnee, pRightFoot, 1);
  SetObjectOrder(this(), pRightKnee, 1);
  SetObjectOrder(pLeftThigh, this(), 1);
  SetObjectOrder(pLeftLeg, pLeftThigh, 1);
  SetObjectOrder(pLeftFoot, pLeftLeg, 1);
  SetObjectOrder(pLeftKnee, pLeftFoot, 1);
  SetAction("Beat");
  SetCon(100);
}

func Destruction() {
  if(pHead) RemoveObject(pHead);
  if(pNeck) RemoveObject(pNeck);
  if(pUpperLeftArm) RemoveObject(pUpperLeftArm);
  if(pUpperRightArm) RemoveObject(pUpperRightArm);
  if(pLeftEllbow) RemoveObject(pLeftEllbow);
  if(pRightEllbow) RemoveObject(pRightEllbow);
  if(pLeftHand) RemoveObject(pLeftHand);
  if(pRightHand) RemoveObject(pRightHand);
  if(pLeftThigh) RemoveObject(pLeftThigh);
  if(pRightThigh) RemoveObject(pRightThigh);
  if(pLeftKnee) RemoveObject(pLeftKnee);
  if(pRightKnee) RemoveObject(pRightKnee);
  if(pLeftFoot) RemoveObject(pLeftFoot);
  if(pRightFoot) RemoveObject(pRightFoot);
  if(pLeftLeg) RemoveObject(pLeftLeg);
  if(pRightLeg) RemoveObject(pRightLeg);
}

func Activity() {
  if(!pHead)
    return(_inherited());
  PlaceHead();
  return(_inherited());
}

func PlaceHead() {
  Local(0) = ((Local(0) + 1) % 360);
  var angle = Sin(Local(0), 45);
  var angle2 = Sin(Local(0), 25);
  var dir = GetDir();
  if(dir==DIR_Right()) {
    pRightLeg->ChangeDef(_YBR);
	pRightLeg->Initialize();
	pLeftLeg->ChangeDef(_YBR);
	pLeftLeg->Initialize();
  } else {
    pRightLeg->ChangeDef(_YBL);
	pRightLeg->Initialize();
	pLeftLeg->ChangeDef(_YBL);
	pLeftLeg->Initialize();
  }
  // Right Leg
  SetDir(dir, pRightFoot);
  
  PlaceR(pRightLeg, 15, -8, -angle2+180-40, -15, pRightFoot, 0, dir);
  PlaceR(pRightThigh, -5, -24, angle2+180+40, -10, pRightLeg, 0, dir);
  Place(pRightKnee, 5, -21, -angle2+180-40, -18, pRightLeg, 15, dir);
  // Left Leg
  Place(pLeftFoot, 30, 0, 0, 0, pRightFoot, 0, dir);
  
  PlaceR(pLeftLeg, 15, -8, -angle2+180-40, -15, pLeftFoot, 0, dir);
  PlaceR(pLeftThigh, -5, -24, angle2+180+40, -10, pLeftLeg, 0, dir);
  Place(pLeftKnee, 5, -21, -angle2+180-40, -18, pLeftLeg, 15, dir);
  // Body
  Place(this(), 16, -32, angle2+180+40, -10, pRightThigh, 0, dir);
  // Head
  PlaceR(pNeck, -30, -65, angle-90+45, 10, 0, 0, dir);
  Place(pHead, -30, -35, 0, 0, pNeck, 0, dir);
}
// Place only
func Place(object obj, int rX, int rY, int angle, int lengthX, object origin, int lengthY, bool mirror) {
  if(!obj) return(0);
  if(!lengthY) lengthY=lengthX;
  SetYDir(0,obj);
  rX += Sin(angle, lengthX);
  rY -= Cos(angle, lengthY);
  if(mirror) {
    rX *= -1;
	SetDir(DIR_Right(), obj);
  } else {
    SetDir(DIR_Left(), obj);
  }
  SetPosition(GetX(origin)+rX, GetY(origin)+rY, obj);
  return(obj);
}
// Place and rotate
func PlaceR(object obj, int rX, int rY, int angle, int length, object origin, int lengthY, bool mirror) {
  if(mirror)
    SetR(-angle, obj);
  else
    SetR(angle, obj);
  return(Place(obj, rX, rY, angle, length, origin, lengthY, mirror));
}