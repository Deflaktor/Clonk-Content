/*-- Monster --*/

#strict
#include _PEM



/* TimerCall mit KI-Steuerung */

Initialize:
  SetColor(2);
  return(Birth());

SetFeuerMonster:
  SetColor(1);
  Local(0)=1;
  return(1);

public func Birth()
{
  SetAction("Walk");
  if (Random(2)) SetComDir(COMD_Left());
  else SetComDir(COMD_Right());
  return(1);
}

private func Activity()
{
  // Nichts machen
  if (Random(2) || (GetAction() ne "Walk" && GetAction() ne "Swim")) return(1);

  // Springen
  if (GetAction() eq "Walk")
   if (!Random(3)) return(DoJump());


  // Feuer speien
  if (GetAction() eq "Walk" && Local(0))
   if (!Random(8)) return(StartFlame());

  // Umsehen
  if (GetAction() eq "Walk")
   if (!Random(8)) return(SetAction("LookUp"));

  // Umdrehen
  if (Random(2)) return(TurnRight());
  return(TurnLeft());
}

public func StartFlame()
{
  if (GetAction() ne "Walk" || GetEffect("IntNoAttack", this())) return();
  AddEffect("IntNoAttack", this(), 1, 140);
  SetAction("Flame");
  Sound("Inflame");
  Sound("Growl*");  
}

private func Flaming()
{
  Var(0)=CreateContents(GameCall("Zufallsflint"));
  SetOwner(GetOwner(), Var(0));
  Exit(Var(0), -15+GetDir()*30, +2, 0, -4+GetDir()*6+Random(2));
  if (GetActTime() > 10) SetAction("Walk");
}

/* Kontakte */

protected func ContactLeft()
{
  return(TurnRight());
}

protected func ContactRight()
{
  return(TurnLeft());
}

/* Aktionen */

public func TurnRight()
{
  if (Stuck() || (GetAction() ne "Walk" && GetAction() ne "Swim")) return();
  if (GetXDir() < 0) SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right()); 
  return(1);
}

public func TurnLeft()
{
  if (Stuck() || (GetAction() ne "Walk" && GetAction() ne "Swim")) return();
  if (GetXDir() > 0) SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left()); 
  return(1);
}

private func HitCheck()
{
  var obj;
  if (obj = FindObject(0, +1,0,0,0, OCF_Prey(), 0,0, NoContainer()))
   if(GetOwner()!=GetOwner(obj))
     Punch(obj, 10);
  return(1);
}

public func DoJump()
{
  if (GetAction() ne "Walk") return();
  if (Random(2)) Sound("Growl*");
  Jump();
}

/* Einwirkungen */
Death:
  Sound("DeathGrowl");
  var threattype = Random(11);
  if(threattype == 10)
  CreateObject(S582,0,0,GetOwner(this()));
  if(threattype < 10)
  CreateObject(ST58,0,0,GetOwner(this()));
  return(RemoveObject());

