#strict
#include HH00

local wait,ttl,nofl;

/* Initialisierung */

protected func Initialize()
{
  SetAction("Walk");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
}

public func Birth()
{
  SetAction("Walk");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
}

check:
if(ttl++>2099)
	return(rechange());
if(wait)
	wait--;
return(1);

/* Kontakt */

ControlRight:

  return(TurnRight());


ControlLeft:

  return(TurnLeft());

ControlDigDouble:
ObjectCall(this(),"rechange");
return(1);


/* Aktionen */

private func Flaming()
{
if(wait){Smoke (-15+GetDir()*30,+2,20); if (GetActTime()>10) SetAction("Walk");
	return();}

  Exit( CreateContents(DFLM), 
        -15+GetDir()*30, +2, 0,
        -4+GetDir()*6+Random(2),0);
  if (GetActTime()>10) {endflame(); SetAction("Walk");}
}

private func endflame()
{
if(!wait)
	wait=175;
}

private func noflame()
{
var ctext,izahl;
izahl=RandomX(1,20);
if(izahl==1)
	ctext="Jetzt gönn mir mal ne Pause!";
if(izahl==2)
	ctext="Pff...";
if(izahl==3)
	ctext="Mir ist so heiß!";
if(izahl==4)
	ctext="AAH!!!|Mein Hals ist voller Brandblasen!";
if(izahl==5)
	ctext="*Hust*";
if(izahl==6)
	ctext="Machs doch selber!";
if(izahl==7)
	ctext="Immer mit der Ruhe.";
if(izahl==8)
	ctext="Nö";
if(izahl==9)
	ctext="Die Sterne stehen ungünstig";
if(izahl==10)
	ctext="Ich bin zu müde!";
if(izahl==11)
	ctext="Du willst mich nur ausnutzen!";
if(izahl==12)
	ctext="Immer cool bleiben!";
if(izahl==13)
	ctext="Ach, lass mich doch!";
if(izahl==14)
	ctext="Ich versuchs ja, aber meine Lunge...";
if(izahl==15)
	ctext="Vielleicht später.";

//ctext=Format("|%s %d/%d",ctext,(175-wait)/175,100);
//ctext=Format("%s|%d von 175 Feuerkraft",ctext,wait);
PlayerMessage (GetOwner(),ctext,this()); 

}

ControlThrow:
if(SEqual(GetAction(),"Flame"))
	return();
if(!wait)
  Sound("Inflame");
if(wait)
	noflame();
  
  SetAction("Flame");
  
  Sound("Growl*");  
return(1);

private func TurnRight()
{
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Right()) if (!SetAction("Turn")) return(0);
  SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right()); 
  return(1);
}

private func TurnLeft()
{
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Left()) if (!SetAction("Turn")) return (0);
  SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left()); 
  return(1);
}

private func HitCheck()
{
  var obj;
  if (obj=FindObject(0, +1,0,0,0, OCF_Prey(),0,0,NoContainer()))
      Punch(obj,10);

  if(Local())
  SetLocal(0,Local()-1);
  return(1);
}

private func ControlUp()
{
  if (Random(2)) Sound("Growl*");
  Jump();
  return(1);
}

private func DoLook()
{
  SetAction("LookUp");
}

public func Reproduction()
{
  
  return(1);
}

/* Einwirkungen */

protected func Death()
{
  Sound("DeathGrowl");
  SetDir(DIR_Left());
  SetAction("Dead");
  rechange();
  Kill();
  return(1);
}
  

UserID:
SetLocal(11,Par());
Birth();
return(1);