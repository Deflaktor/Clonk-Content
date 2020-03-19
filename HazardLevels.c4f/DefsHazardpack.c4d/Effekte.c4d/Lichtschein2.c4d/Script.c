#strict

local red, green, blue, alpha;

// Lichtschein an das gewünschte Objekt erzeugen
global func Enlighten(target_obj, _red, _green, _blue, _alpha, _size) {
  var light = CreateObject(_LGO, GetX(target_obj), GetY(target_obj), -1);
  ObjectCall(light, "Activate", target_obj, _red, _green, _blue, _alpha, _size);
  return(light);
}

// Position an Zielobjekt anpassen
protected func Adjust() {
  SetPosition(GetX(GetActionTarget()), GetY(GetActionTarget()));
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
}

protected func Flicker() {
  // Ziel zerstört?
  if (!GetActionTarget()) return(RemoveObject());
  // Flackern
  alpha = BoundBy(alpha+RandomX(-5, +5), 0, 255);
  SetClrModulation(RGBa(red, green, blue, alpha));
}