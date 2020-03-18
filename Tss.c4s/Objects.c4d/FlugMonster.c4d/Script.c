/* FlugMonster */

#strict

local Stopped;

protected func Initialize()
{
SetAction("Fly");
SetComDir(COMD_Right()); SetDir(DIR_Right());
if (Random(2)) { SetComDir(COMD_Left()); SetDir(DIR_Left());}
return(1);
}

public func Birth()
{
  SetAction("Fly");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
}

private func Activity()
{
//  var arrow = FindObject(0,-27,-32,55,63,0,"Stick");
//  if (arrow) return(Death() && ObjectSetAction(arrow,"Idle"));
  return(KramMachen());
}

protected func KramMachen()
{
  // Nichts machen
  if (Random(2)) return(1);
  // Nur im Fliegen
  if (GetAction()ne"Fly") return(1);
  // Hoch oder runter fliegen
  SetComDir(COMD_Up());
  if (Random(2)) SetComDir(COMD_Down());
  // Nach links oder nach rechts oder so bleiben
  if (!Random(4)) return(1);
  if (Random(2)) { SetComDir(COMD_Right()); SetDir(DIR_Right()); }
  if (Random(2)) { SetComDir(COMD_Left()); SetDir(DIR_Left()); }
}

protected func Survive() {
  var xdir = GetXDir();
  var ydir = GetYDir();
  var danger = InLiquid();
  if (!danger) {
    danger = GBackLiquid(xdir * 2, ydir * 2);
    if (!danger) {
      danger = GBackLiquid(xdir * 3, ydir * 3);
      if (!danger)
        danger = FindObject(0, -20 + xdir * 2, -20 + ydir * 2, 40, 40, OCF_OnFire());
    }
  }
  if (danger) SetComDir(COMD_Up());
}
  
protected func ContactLeft() 
{ 
  SetComDir(COMD_Right());
  SetDir(DIR_Right());
}

protected func ContactRight() 
{ 
  SetComDir(COMD_Left());
  SetDir(DIR_Left());
}

protected func ContactBottom() 
{ 
  if (!Random(20)) return(Landen());
  SetComDir(COMD_Up());
}

protected func ContactTop()
{
  SetComDir(COMD_Down());
}

Landen:		 // Landen
{
  Sound("Ende");  
  ChangeDef(_FMN);
  SetAction("Walk");
  SetPosition(GetX(), GetY() + 8);
  if (!Stopped){
  SetComDir(COMD_Right());
  if(Random(2)) SetComDir(COMD_Left());}
  return(1);
}

ControlDig:			 // Luftfeuer-Meteoriten speien
{

if (GetDir()!=DIR_Right()){
  CastParticles("MSpark",30,30,-24,6, 100, 200,  RGBa(100,100,255,128), RGBa(0,0,255,0));}
if (GetDir()!=DIR_Left()){
  CastParticles("MSpark",30,30,24,6, 100, 200,  RGBa(100,100,255,128), RGBa(0,0,255,0));}

Sound("Growl*");  
SetAction("FlySpei");
  {
    if (GetDir()!=DIR_Left()){
      SetXDir(60,SetLocal(0,CreateObject(ARF2,26,6)));
      SetYDir(0,Local());}
    if (GetDir()!=DIR_Right()){
      SetXDir(-60,SetLocal(0,CreateObject(ARF2,-26,6)));
      SetYDir(0,Local());}
  }
SetLocal(1,Sum(Local(1),-Sum(Local(1))));
return(1);
}


private func End()
{
if (GetActTime()>8) SetAction("Fly");
}

Swimming:
{
if (GBackSemiSolid(0,15))
  {
  SetComDir(COMD_Up());
  SetPosition(GetX(), GetY() - 10);
  }
Sound("Splash*");
return(SetAction("Fly"));
}


protected func Death()
{
  Sound("DeathGrowl");
  SetDir(DIR_Left());
  ChangeDef(DAMN);
  SetAction("Dead");
  return(1);
}

public func IsStill() {return(0);}
public func IsArrowTarget() {return(1);}