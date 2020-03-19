#strict

local red, green, blue, alpha;

global func EnlightenKegel(target_obj, _red, _green, _blue, _alpha, _size) {
  var light = CreateObject(_LGK, GetX(target_obj), GetY(target_obj), -1);
  ObjectCall(light, "Activate", target_obj, _red, _green, _blue, _alpha, _size);
  return(light);
}


private func Adjust()
 {
 var con = Contained(GetActionTarget());
 if ( GetID(con) == HZCK && !Contained(con) ) SetR( -86 + 172 * GetDir(con) + ( BoundBy(GetYDir(con), -60, 60)*(-1+2*GetDir(con)) ) );

 SetPosition(GetX(GetActionTarget())+GetVertex(0,0), GetY(GetActionTarget())+GetVertex(0,1));
 if (!GetActionTarget()) return(RemoveObject());

 alpha = BoundBy(alpha+RandomX(-1, +1), 0, 255);
 SetClrModulation(RGBa(red, green, blue, alpha));
 }

public func Activate(target_obj, _red, _green, _blue, _alpha, _size) {
  // Standardgröße von 20
  var size = _size;
  if (!_size) size = 20;

  SetAction("Attach", target_obj);
  SetCon(size);
  red = _red;
  green = _green;
  blue = _blue;
  alpha = _alpha;
  SetClrModulation(RGBa(red, green, blue, alpha));
}

private func Timer() {

}