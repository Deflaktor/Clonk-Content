#include BIK1

Fahren:
  if(Not(Local(1)))
  Redefine(BIK1);
  if(Local(1))
  SetLocal(1,Local(1)-1);
  if(Not(Local(1)))
  SetLocal();
  AssignVar(0,+60+Local());
  if(Equal(GetDir(),DIR_Left())) AssignVar(0,-60-Local());
  SetXDir(Var(0));
  AssignVar(1,-15);
  if(Equal(GetDir(),DIR_Left())) AssignVar(1,+15);
  return(1);