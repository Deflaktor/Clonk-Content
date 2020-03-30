/*-- Schlange --*/

#strict
#include HH00

HitCheck:
  if(Local())
  SetLocal(0,Local()-1);
 return(1);

ControlDigDouble:
ObjectCall(this(),"readyrechange");
return(1);


ControlThrow:
if(Local())
  return();



if (Var(0)=FindObject(0, -13+26*GetDir(),0,0,0, OCF_Prey()))
    if (GetAlive(Var(0)))
    {
      SetLocal(0,10);
      Attack(Var(0));
    }
return();


ControlLeft: return(TurnLeft());
ContactRight: return(TurnRight());

TurnRight:
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Right()) if (!SetAction("Turn")) return(0);
  SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right()); 
  return(1);

TurnLeft:
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Left()) if (!SetAction("Turn")) return (0);
  SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left()); 
  return(1);

Attack:
  Sound("Snake*");
  Punch(Par(0),8);
  return(1);

DoJump:
  Jump();
  return(1);

Death:
  SetDir(0);
  rechange();
  Kill();
  return(1);

Completion:
  SetAction("Walk");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
  return(1);

Birth:
  Completion();
  return(1);

Cook:
	ChangeDef(CSNK);
	return(1);

UserID:
SetLocal(11,Par());

SetLocal(10,GetPhysical("CorrosionResist", 2,this()));
if(!Local(10))
  SetPhysical( "CorrosionResist", 1, 2,this());

Birth();
return(1);

readyrechange:

if(!Local(10))
  SetPhysical( "CorrosionResist", 0, 2,this());
rechange();
return();