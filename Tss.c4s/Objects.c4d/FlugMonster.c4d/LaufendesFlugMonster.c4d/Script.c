/*-- Flugmonster --*/

#strict
#include ANIM

private func ReproductionRate()    { return(2000); } // Die Chance, dass in einem Timerintervall eine Vermehrung stattfindet
private func MaxAnimalCount()      { return(4);}     // Maximale Tieranzahl im Umkreis

local Stopped,Free,energie;

/* Initialisierung */

protected func Initialize()
{
  SetAction("Walk");
  DoMagicEnergy(-50);
  if (GetOwner() != -1) Stopped = 1;
  if (!Stopped) {
    SetComDir(COMD_Left());
    if (Random(2)) SetComDir(COMD_Right());
  }
}

public func Birth()
{
  SetAction("Walk");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
}

/* TimerCall */

private func Activity()
{
  if(!energie){
  SetLocal(1,Sum(Local(1),+1));
  if(GreaterThan(Local(1),9)) energie=1;}
  if (Contained()) {
    Stopped = 1;
    return(AppendCommand(this(), "Exit"));}
  AdjustSeatVertex();
  DoMagicEnergy(+5);
  if (Free) return(KramMachen());
  if (!GetRider() && !Stopped) return(KramMachen());
}

protected func KramMachen()
{
  // Nichts machen
  if (Random(2)) return(1);
  // Nur im Gehen oder Schwimmen
  if (GetAction()ne"Walk"&&GetAction()ne"Swim") 
    return(1);
  // Ein Ei legen
  if (!Random(ReproductionRate())) 
    Reproduction();	
  // Springen
  if (GetAction()S="Walk")
    if (!Random(3)) return(DoJump());
  // Flieeegään
  if (GetAction()S="Walk")
    if (!Random(10)) return(Fly());
  // Umsehen
  if (GetAction()S="Walk")
    if (!Random(8)) return(DoLook());
  // Umdrehen
  if (Free) {
   if (Random(2)) { SetComDir(COMD_Left());  SetDir(DIR_Left()); AdjustSeatVertex(); return(0);} else {
   SetComDir(COMD_Left()); SetDir(DIR_Left()); AdjustSeatVertex(); return(0);}} else {
  if (Random(2)) return(TurnRight());
  return(TurnLeft());}
}

/* Kontakt */

protected func ContactLeft()
{
  if (Free) {
   SetComDir(COMD_Right());
   SetDir(DIR_Right());
   AdjustSeatVertex();}
  if (!GetRider() && !Stopped){
   return(TurnRight());
}
}

protected func ContactRight()
{
  if (Free) {
   SetComDir(COMD_Left());
   SetDir(DIR_Left());
   AdjustSeatVertex();}
  if (!GetRider() && !Stopped){
   return(TurnLeft());
}
}

/* Aktionen */

private func TurnRight()
{
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Right()) if (!SetAction("Turn")) return(0);
  SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right()); 
  AdjustSeatVertex();
  return(1);
}

private func TurnLeft()
{
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Left()) if (!SetAction("Turn")) return (0);
  SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left()); 
  AdjustSeatVertex();
  return(1);
}

private func DoJump()
{
  if (Random(2)) Sound("Growl*");
  Jump();
  return(1);
}


private func DoLook()
{
  SetAction("LookUp");
}

// Vermehrung
private func CountMe()
{
  var ReprodSize = ReproductionAreaSize();
  var ReprodSizeHalb = ReprodSize  / -2;
   return(ObjectCount(_FMN, ReprodSizeHalb, ReprodSizeHalb, ReprodSize , ReprodSize , OCF_Alive())
	 +ObjectCount(AMEG, ReprodSizeHalb, ReprodSizeHalb, ReprodSize , ReprodSize , 0));
}

private func SpecialRepr()
{
  Exit(CreateContents(AMEG),+0,+10);
  return(1);
}

Swimming:
{
if (GBackSemiSolid(0,5)) 
  {
  SetComDir(COMD_Up());
  SetPosition(GetX(), GetY() - 2);
  }
Sound("Splash*");
return(Fly());
}

/* Einwirkungen */

protected func Death()
{
  Sound("DeathGrowl");
  SetDir(DIR_Left());
  ChangeDef(DAMN);
  SetAction("Dead");
  return(1);
}

protected func Fly()
{
  Sound("Start");
  ChangeDef(_FM1);
  SetAction("Fly");
  SetComDir(COMD_Up());
  return(SetPosition(GetX(), GetY() - 10));
}

protected func ActivateEntrance(caller)
{
  if(GetRider()) return(Jump(caller));
  if(ObjectSetAction(Par(0),"Ride",this())) return(1,Message("%s: Los geht's !",Par(0),GetName(Par(0))));
  SetEntrance(1);
  SetObjectOrder(this(),0);
  AdjustSeatVertex();
  return(1);
}

GetRider:
 if(SetVar(0,FindObject(0,0,0,0,0,0,"RideStill",this()))) return(Var(0));
 return(FindObject(0,0,0,0,0,0,"Ride",this()));

private func AdjustSeatVertex()
{
SetVar(0,-8);
  if (Equal(GetDir(),DIR_Right())) SetVar(0,Mul(Var(0),-1));
  SetVertex(0,0,Var(0));
  return(1);
}

Sitting:
{
  AdjustSeatVertex();
  return(1);
}

/* Steuerung */


ControlUp:                                   // springen
{
  if (Random(2)) Sound("Growl*");
  Jump();
  Stopped = 0;
  AdjustSeatVertex();
  return(1);
}

ControlDownSingle:                      // stehen bleiben
{
  if (GetAction() ne "Jump") {
    SetComDir(COMD_Stop());
    AdjustSeatVertex();
    Stopped = 1;}
  return(1);
}

ControlLeft:                                     // links
{
  SetComDir(COMD_Left());
  SetDir(DIR_Left());
  AdjustSeatVertex();
  Stopped = 0;
  return(1);
}

ControlRight:                                   // rechts
{
  SetComDir(COMD_Right());
  SetDir(DIR_Right());
  AdjustSeatVertex();
  Stopped = 0;
  return(1);
}


ControlDownDouble:                        // Abspringen
{
  if (Free) Free = 0;
  if (Equal(Par(0),GetRider()))
  return(ObjectSetAction(Par(0),"Walk"));
  ActivateEntrance();
  return(1);
}

ControlUpDouble:                             // Flieeegään
{
  Sound("Start");
  SetPosition(GetX()-1, GetY() - 10);
  ChangeDef(_FM1);
  SetAction("Fly");{
  if(Random(2)){
  if(ObjectSetAction(Par(0),"Ride",this())) Message("Yeehaaw !",Par(0),GetName(Par(0)));}
  else{
  if(ObjectSetAction(Par(0),"Ride",this())) Message("Juuhuuuu !",Par(0),GetName(Par(0)));}}
  AdjustSeatVertex();
  return(1);
}

ControlDig:                                        // Frei rumlaufen lassen
{
if (Free){Free = 0;
return(Message("Nicht mehr frei !",this()));}
if (!Free){Free = 1;
return(Message("Frei !",this()));}
}

private func End()
{
AdjustSeatVertex();
if (GetActTime()>10) {
  if (!Stopped){
    SetAction("Walk");
    return(1);}
  else{
    SetAction("Walk");
    SetComDir(COMD_Stop());
    Stopped = 1;
    return(1);}}
return(1);
}

public func IsStill() {if (Stopped) return(1); return(0);}
public func IsHorse() {return(1);}