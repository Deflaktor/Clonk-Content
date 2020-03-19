#strict
#include _WOM

local power;

Initialize:
  Farbe();
  return(1);

public isWeapon:
  return(ShortRangeWeapon()|MiddleRangeWeapon()|LongRangeWeapon());

public MinRange:
  return(5);

public MaxRange:
  return(400);

Farbe:
  SetPicture(11,0,60,38);
  PhaserSetColorByPower(power);
  return(1);

global PhaserSetColorByPower:
  var power=Par(0);
  if(power>-1) {
    // Farbe blau gibt es nicht, damit man nicht mit schallpistole verwechselt
    // Außerdem ist grün die erste Farbe.
    if(power==0) SetColor(2,Par(1));
	if(power==1) SetColorDw(RGBa(50, 250, 125, 0), Par(1));
	if(power==2) SetColorDw(RGBa(0, 250, 250, 0), Par(1));
	if(power==3) SetColorDw(RGBa(0, 127, 250, 0), Par(1));
	if(power==4) SetColorDw(RGBa(100, 100, 175, 0), Par(1));
	if(power==5) SetColorDw(RGBa(127, 0, 250, 0), Par(1));
	if(power==6) SetColorDw(RGBa(250, 0, 250, 0), Par(1));
	if(power==7) SetColorDw(RGBa(127, 127, 0, 0), Par(1));
	if(power==8) SetColorDw(RGBa(250, 250, 0, 0), Par(1));
	if(power==9) SetColorDw(RGBa(250, 127, 0, 0), Par(1));
	if(power==10) SetColorDw(RGBa(250, 0, 0, 0), Par(1));
	if(power==11) SetColorDw(RGBa(175, 100, 175, 0), Par(1));
	if(power==12) SetColorDw(RGBa(175, 175, 100, 0), Par(1));
	if(power==13) SetColorDw(RGBa(100, 175, 175, 0), Par(1));
	if(power==14) SetColorDw(RGBa(250, 250, 250, 0), Par(1));
	if(power==15) SetColorDw(RGBa(50, 50, 50, 0), Par(1));
  } else {
    // Dead Code
    if(power>=2)
      power++;
    else if(power==0)
      power=2;
    SetColor(power,Par(1));
  }
  return(1);
  
Reloaden:
  Farbe();
  return(_inherited());

GetPower:
  return(power);

Activate:
  var maxPower = 10;
  var i;
  if(i = GameCall("MaxPhasorPower")) maxPower = i;
  if(power>=maxPower)
    return(Sound("NoAmmo"));
  // Beim Träger nach Ammo suchen
  if(Not(SetVar(0,FindObject(GetID(),-1,-1,2,2,0,0,0,Contained(),0))))
    return(Sound("NoAmmo"));
  if(Var(0)==this())
    return(Sound("NoAmmo"));
  if(ObjectCall(Var(0),"GetPower")>=maxPower)
    return(Sound("NoAmmo"));
  // Ammo nehmen
  power+=ObjectCall(Var(0),"GetPower");
  power++;
  if(power>maxPower)
    power=maxPower;
  RemoveObject(Var(0));
  Sound("SpellSysMenu1");
  return(1);

SelectionSound:
  Sound("Bip2");
  return(1);

ShotSound:
  Sound("Phasor1");
  return(1);
  
Shot:
  // Ammo abfeuern
  Exit(Par(0), Par(1)*24-12,power/2,0, 0,0,0 );
  ObjectCall(Par(0),"Launch",Par(1),power);
  return(1);

/* Ammo ID */  
GetAmmoID:
  return(_AM1);

Dmg:
  return(DefinitionCall(GetAmmoID(), "Dmg", power));
