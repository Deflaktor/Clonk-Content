/*-- *bounce* --*/

#strict

protected Initialize: return(SetAction("Flicker"));

protected Bounce:
  while(Var(0)=FindObject(0, -10, -15, 20, 30, OCF_CrewMember(), 0, 0, NoContainer(),Var()))
    {
    Fling(Var(0), -1, -9);
    Sound("BOING", 0, Var(0));
    }
  return(1);
