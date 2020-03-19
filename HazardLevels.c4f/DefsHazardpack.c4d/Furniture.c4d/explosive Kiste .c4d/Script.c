#strict

Initialize:
  return(1);


Hit:
  Sound("RockHit*");
  return(1);

Damage:
  if ( LessThan( GetDamage(), 30 ) ) return(0);
  // Crack open
  while (Contents()) Exit(Contents());
  // On Fire?
  if(OnFire()) {
    CastObjectsFire(_CF1,1,20,0,-10);
    CastObjectsFire(_CF2,5,20,0,-10);
  } else {
    CastObjects(_CF1,1,20,0,-10);
    CastObjects(_CF2,5,20,0,-10);
  }
  CastObjects(DFLM,5,20,0,-10);
  Sound("CrateCrack");
  Sound("Blast1");
  RemoveObject();
  ObjectCall(CreateObject(EXPL),"Launch",60);
  return(1);

CastObjectsFire:
  var id, am, lev, x, y, ang, obj, xdir;
  id = Par(0);
  am = Par(1);
  lev = Par(2);
  x = Par(3);
  y = Par(4);
  for(var i=0;i<am;i++) {
    ang=Random(360);
    SetR(Random(360),obj=CreateObject(id,x,y,-1));
    SetXDir(xdir=Cos(ang,lev)+RandomX(-3,3),obj);
    SetYDir(Sin(ang,lev)+RandomX(-3,3),obj);
    SetRDir((10+Random(21))*xdir/Abs(xdir),obj);
    Incinerate(obj);
  }
  return(obj);