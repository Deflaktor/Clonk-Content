/*-- *bounce* --*/

#strict

protected Initialize: return(SetAction("Flicker"));

protected Bounce:
  if(Var(0)=FindObject(BIK1, -40, -30, 40, 30, 0, 0, 0, NoContainer(),Var()))
    {
    SetRDir(14,Var());
    SetYDir(GetYDir(Var())-32,Var());
//    if(Not(Local(1,Var())))
    SetLocal(0,400,Var(0));
//    if(Not(Local(1,Var())))
    SetLocal(1,105,Var(0));
    if(Not(Local(1,Var())))

    SetVar(1,GetAction(Var()));
    SetVar(2,GetYDir(Var()));
    SetVar(3,GetXDir(Var()));
    SetVar(4,GetRDir(Var()));
    ChangeDef(BIK2,Var());
    ObjectSetAction(Var(),"Act3");
    SetYDir(Var(2),Var());
    SetXDir(Var(3),Var());
    SetRDir(Var(4),Var());

    ObjectCall(Var(),"Redefine",BIK2);
    Sound("nitro", 1, Var(0));
    }
  return(1);
