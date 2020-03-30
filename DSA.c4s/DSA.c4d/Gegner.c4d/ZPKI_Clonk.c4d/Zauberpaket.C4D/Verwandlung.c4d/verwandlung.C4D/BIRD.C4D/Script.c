//Author wie immer Major aber das hier liest ja eh niemand also was solls}
/*-- Vogel --*/

#strict
#include HH00

ControlThrow:
  if (!(Var()=FindObject(BALN, -15,0,30,25))) Var()=FindObject(BLMP, -25,0,50,30);
  if (Var(0)) Attack(Var()); 
  return(1);

HitCheck:
return();

ControlDown:
SetComDir(COMD_Stop());
return(1);

ControlRight:
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Right()) if (!SetAction("Turn")) return (0);
  SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right()); 
  return(1);

ControlUp:
  if (Stuck()) return(0);
  
  if (GetComDir()!=COMD_Up())
    
  SetComDir(COMD_Up()); 
  return(1);

ControlDown:
  if (Stuck()) return(0);
  
  if (GetComDir()!=COMD_Down())
    
  SetComDir(COMD_Down()); 
  return(1);


ControlLeft:
  if (Stuck()) return(0);
  if (GetDir()!=DIR_Left()) if (!SetAction("Turn")) return (0);
  SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left()); 
  return(1);

Attack:
  ObjectCall(Par(0),"Poke");
  SetAction("Attack");
  Sound("Raven*");
  return(1);

RejectCollect:
  if ( Par()==ARRW || Par()==FARW || Par()==XARW )
    return(0);
  return(1);

Collection: 
  Sound("RavenHurt");
  SetAction("Tumble");
  return(1);

CatchBlow:
  if (!Random(3)) Sound("RavenHurt");
  return(1);

Completion:
  SetAction("Fly");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
  return(1);

Death:
  ChangeDef(Local(11));
  Kill();
  return(1);

UserID:
SetLocal(11,Par());
SetLocal(10,GetPhysical("Float", 2,this()));
if(!Local(10))
	SetLocal(10,GetPhysical("Float", 1,this()));
SetPhysical ("Float",200,2); 


Completion();
return(1);

readyrechange:
SetPhysical("Float",Local(10), 2,this());
rechange();
return(1);

ControlDigDouble:
ObjectCall(this(),"readyrechange");
return(1);