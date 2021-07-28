#strict

static fleijaGrowSizes;

local growTime, shrinkTime;

protected func Launch() {
  // formula for sizes using WolframAlpha: Table[4000. * ( -2^(-10 * t/84 ) + 1 ) + 100, {t,0,84}]
  // convert plain output text using regex: MATCH \..*?, REPLACE , 
  if(!fleijaGrowSizes)
    fleijaGrowSizes = [100, 416, 708, 977, 1224, 1452, 1661, 1855, 2032, 2196, 2347, 2486, 2614, 2731, 2840, 2939, 3031, 3116, 3194, 3266, 3332, 3392, 3448, 3500, 3547, 3591, 3631, 3669, 3703, 3734, 3763, 3790, 3814, 3837, 3858, 3877, 3894, 3911, 3926, 3939, 3952, 3964, 3975, 3984, 3994, 4002, 4010, 4017, 4023, 4029, 4035, 4040, 4045, 4049, 4053, 4057, 4060, 4063, 4066, 4069, 4071, 4073, 4076, 4077, 4079, 4081, 4082, 4084, 4085, 4086, 4087, 4088, 4089, 4090, 4091, 4091, 4092, 4093, 4093, 4094, 4094, 4095, 4095, 4095, 4096];
  growTime = 84;
  shrinkTime = growTime/3;
  Sound("FleijaBlast");
  Sound("FleijaBlastB");
  SetAction("Shockwave");
  SetCategory(C4D_Foreground);
  SetCon(1);
  return(1);
}

Dmg:
  return(280);

public func DestroyMaterials() {
  return(0);
}

private func GetRadius() {
  return(90*5*GetCon()/100/100);
}

private func GetMaxRadius() {
  return(90*5*fleijaGrowSizes[growTime]/100/100);
}

protected func ResizeGrow() {
  var target = fleijaGrowSizes[GetActTime()];
  var current = GetCon();
  DoCon(Max((target - current)*1,0));
  var radius = GetRadius();
  if(GetActTime()>=growTime-1) {
    if(DestroyMaterials()) {
      VieleckZeichnen("Earth", radius, 72);
    }
    DigFree(GetX(),GetY(),Min(GetCon()+10, radius+3));
    SetAction("ShockwaveShrink");
  } else if(GetActTime()%5==0) {
    if(DestroyMaterials()) {
      var ecken = BoundBy(8 + 8*radius/100 - 6*radius*radius/100000,8,36);
      VieleckZeichnen("Earth", radius, 2*ecken/3);
    }
    DigFree(GetX(),GetY(),Min(GetCon()+10, radius+3));
  }
  DealDamage();
  return(1);
}

protected func ResizeShrink() {
  var target = fleijaGrowSizes[Max(growTime-GetActTime()*growTime/shrinkTime,0)];
  var current = GetCon();
  DoCon(target - current);
  if(GetActTime()==shrinkTime/2)
    Sog(100);
  if(GetActTime()<shrinkTime/2)
    DealDamage();
  if(GetActTime()>=shrinkTime)
    RemoveObject();
  return(1);
}

private func DealDamage() {
  var radius = GetRadius();
  var hitSomeone = 0;
  var obj;
  while (obj=FindObject(0,-radius,-radius,radius*2,radius*2,0,0,0,NoContainer(),obj)) {
    if(GetAlive(obj))
      hitSomeone = 1;
    DoEnergy(-2,obj);
    DoDamage(2,obj);
    var xSpd = GetX()-GetX(obj);
    var ySpd = GetY()-GetY(obj);
    Fling(obj,0,-10);
    if(GetCategory(obj) & C4D_Object()||GetCategory(obj) & C4D_Living()||GetCategory(obj) & C4D_Vehicle())
      if(!SEqual(GetProcedure(obj),"ATTACH"))
        if(GetID(obj)!=_HGG)
          if(GetOCF(obj)&OCF_Prey())
            SetSpeed(-xSpd/3,-ySpd/3-10,obj);
          else
            SetSpeed(-xSpd/8,-ySpd/8-10,obj);
  }
  if(hitSomeone)
    Sound("ProjectileHit*");
}

private func Sog(int power) {
  var obj;
  var radius = 3*GetMaxRadius()/2;
  while (obj=FindObject(0,-radius,-radius,radius*2,radius*2,0,0,0,NoContainer(),obj)) {
    if(GetCategory(obj) & C4D_Object()||GetCategory(obj) & C4D_Living()||GetCategory(obj) & C4D_Vehicle())
      if(!SEqual(GetProcedure(obj),"ATTACH"))
        if(GetID(obj)!=_HGG)
          CheckSog(obj, power);
  }
}

private func CheckSog(object obj, int power) {
  if (GetMaterial(GetX(obj),GetY(obj))==Material("Earth")) return(1);
  Fling(obj,0,-10);
  var dist = ObjectDistance(obj);
  var angle = Angle(GetX(obj),GetY(obj),GetX(),GetY()-30);
  var speed = BoundBy(power+GetMaxRadius()-dist,0,150);
  var xspd = Sin(angle,speed);
  var yspd = -Cos(angle,speed);
  SetSpeed(xspd,yspd,obj);  
  if(SEqual(GetAction(obj),"Travel")) {
    SetLocal(0,xspd,obj);
    SetLocal(1,yspd,obj);
  }
  return(1);
}

protected func Remove() {
  RemoveObject();
  return(1);
}

VieleckZeichnen:
  var material = Par(0);
  var radius = Par(1);
  var ecken = BoundBy(Par(2), 3, 360);
  var x = GetX() + Par(3);
  var y = GetY() + Par(4);
  var underground = 1;
  for (var winkel = 0; winkel<360; winkel+=360/ecken) {
    var x1, x2, y1, y2;
    x1 = x + Sin(winkel, radius);
    y1 = y + Cos(winkel, radius);
    if(GetMaterial(x1 - GetX(), y1 - GetY())==Material("Sky"))
      underground = 0;
  }
  for (var winkel = 0; winkel<360; winkel+=360/ecken) {
    var x1, x2, y1, y2;
    x1 = x + Sin(winkel, radius);
    y1 = y + Cos(winkel, radius);
    x2 = x + Sin(winkel+360/ecken, radius);
    y2 = y + Cos(winkel+360/ecken, radius);
    DrawMaterialQuad(material,x,y,x1,y1,x2,y2,x,y,underground);
  }
  return(1);