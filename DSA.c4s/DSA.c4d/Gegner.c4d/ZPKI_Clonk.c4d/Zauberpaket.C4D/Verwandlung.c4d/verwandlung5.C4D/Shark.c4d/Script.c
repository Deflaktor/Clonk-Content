/*-- Hai --*/

#strict
#include HH00

/* Initialisierung */

protected Initialize:
  SetAction("Swim");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
  return(1);

/* Aktivit‰t */

private Swimming:
  if (Var(0)=FindObject(0, -20+40*GetDir(),0,0,0, OCF_Prey()))
    if (GetAlive(Var(0)))
      if (!Contained(Var(0)))
        Attack(Var(0));
  return(1);


/* Aktionen von auﬂerhalb */

public Eat:
  ObjectCall(Par(0),"Feed",100);
  RemoveObject();
  return(1);
  
/*public Kill:
  DoEnergy(-100);
  return(0);
*/
 
/*public Cook:
	ChangeDef(CSHK);
	return(1);*/

/* Kontakt */

protected ControlRight:
  return(TurnRight());
  
protected ControlLeft:
  return(TurnLeft());

protected ControlDown:
  SetComDir(COMD_Down());
  return(1);

ControlDig:
if (Var(0)=FindObject(0, -250,-100,500,200, OCF_Prey(), "Swim"))
    SetCommand(this(),"Follow",Var(0));
return(1);

ControlDigDouble:
readyrechange();
return(1);

protected ControlUp:
  if (GetAction()ne"Walk") SetComDir(COMD_Up());
  
  return(1);

/* Bewegung */

private TurnRight:
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Right()) SetAction("Turn");
  SetXDir(0);
  SetDir(DIR_Right());
  if (GetComDir()==COMD_Left()) 
    SetComDir(COMD_Right()); 
  return(1);

private TurnLeft:
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Left()) SetAction("Turn");
  SetXDir(0);
  SetDir(DIR_Left());
  if (GetComDir()==COMD_Right()) 
    SetComDir(COMD_Left()); 
  return(1);

/* Aktionen */

private Attack:
  SetAction("Jaw");
  Sound("Munch1");
  Punch(Par(0),8);
  return(1);

protected Death:
  SetDir(0);
  SetAction("Dead");
  rechange();
  Kill();
  return(1);

public Reproduction:
  
  return(1);

public Birth:
  SetAction("Swim");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
  return(1);


readyrechange:

if(!Local(10))
  SetPhysical( "BreatheWater", 0, 2,this());


rechange();
return();

UserID:
SetLocal(11,Par());
SetLocal(10,GetPhysical("BreatheWater", 2,this()));
if(!Local(10))
  SetPhysical( "BreatheWater", 1, 2,this());

Birth();
return(1);
