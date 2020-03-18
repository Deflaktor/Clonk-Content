/*-- Neues Objekt --*/

#strict

Initialize:
  SetPosition(GetX(), GetY() + 100);
  SetAction("Blast");
  DigFree(GetX(),GetY(),100);
  Sound("WExplosion*");
  while(SetVar(0,FindObject(0, -75,-75,150,150,0,0,0,NoContainer(),Var(0)))) Repel(Var(0));

  var ang, obj, xdir, lev;

  // Dark Smoke
  lev = 30;
  for(var i=0;i<15;i++) {
    ang=Random(360);
    SetR(Random(360),obj=CreateObject(KACD,0,0,GetOwner()));
    SetXDir(xdir=Cos(ang,lev)+RandomX(-3,3),obj);
    SetYDir(Sin(ang,lev)+RandomX(-3,3),obj);
    SetRDir((10+Random(21))*xdir/Abs(xdir),obj);
    SetObjectOrder(Var(1), obj);
  }

  // Fire
  lev = 40+Random(40);
  for(var i=0;i<10;i++) {
    ang=270+Random(210) - 210/2;
    SetR(Random(360),obj=CreateObject(KACF,0,0,GetOwner()));
    SetXDir(xdir=Cos(ang,lev)+RandomX(-3,3),obj);
    SetYDir(Sin(ang,lev)+RandomX(-3,3),obj);
    SetRDir((10+Random(21))*xdir/Abs(xdir),obj);
    SetObjectOrder(Var(1), obj);
  }

  // Light Smoke
  lev = 50;
  for(var i=0;i<15;i++) {
    ang=Random(360);
    SetR(Random(360),obj=CreateObject(KACS,0,0,GetOwner()));
    SetXDir(xdir=Cos(ang,lev)+RandomX(-3,3),obj);
    SetYDir(Sin(ang,lev)+RandomX(-3,3),obj);
    SetRDir((10+Random(21))*xdir/Abs(xdir),obj);
    SetObjectOrder(Var(1), obj);
  }

  // Ellipse
  obj=CreateObject(KACL,0,0,GetOwner());
  obj->SetAction("Justify", this());
  SetObjectOrder(obj);

  // Poot!
  obj=CreateObject(KACP,0,0,GetOwner());
  obj->SetAction("Justify", this());

  return(1);

Repel:
  if(GetMass(Par(0))<=1)
    return(1);
  var dist, ang, lev;
  dist = Distance(GetX(), GetY(), GetX(Par(0)), GetY(Par(0)));
  lev = (135-dist)*3/2;
  ang = Angle(GetX(), GetY(), GetX(Par(0)), GetY(Par(0)));
  // Log(Format("Angle: %i Distance: %d X: %d Y: %d", ang, dist, Sin(ang,lev), -Cos(ang,lev)));
  if(GetX()==GetX(Par(0)))
    ang = -45+Random(90);
  if(lev<=0) 
    return(1);
  Fling(Par(0),0,-10);
  SetSpeed(Sin(ang,lev)-2+Random(4), -Cos(ang,lev)-2+Random(4),Par(0));
  var dmg;
  dmg = Min(lev/2+2, 100);

  if( !ObjectCall(Par(0), "NoShiftOwner") && GetMass(Par(0))>1 && (GetOCF(Par(0)) & OCF_Collectible()) && !GetYDir(Var(0)) && !GetXDir(Var(0)))
    SetOwner(GetOwner(),Par(0));


  if(GetAlive(Par(0))) {
    Var(0)=Par(0)->CreateObject(__SA);
    Var(0)->Local(0)=dmg;
  }
  DoEnergy(-dmg, Par(0));
  DoDamage(dmg, Par(0));
  return(1);

Remove:
  RemoveObject();
  return(1);