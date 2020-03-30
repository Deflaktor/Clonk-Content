/*-- *bounce* --*/

#strict

protected Initialize: return(SetAction("Flicker"));

protected Bounce:
  if(Var(0)=FindObject(BIK1, -40, -30, 80, 60, 0, 0, 0, NoContainer(),Var()))
    {
//    if(Not(Local(1,Var())))
    SetLocal(0,60,Var(0));
//    if(Not(Local(1,Var())))
    SetLocal(1,90,Var(0));
    if(Not(Local(1,Var())))
    Sound("nitro", 1, Var(0));
    }
  return(1);
