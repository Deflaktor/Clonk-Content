Initialize:
  SetAction("10");
  return(1);

Attach:
  SetLocal(0,Par(0));
  return(1);

FixPos:
  if(!Local(0))
    RemoveObject();
  SetPosition(GetX(Local(0)),Sub(GetY(Local(0)),17),this());
  return(1);

CheckEnergy:
  SetVar(0,Local(0,Local(0)));
  if(GreaterThan(Var(0),99)) if(LessThan(Var(0),101)) if(Not(SEqual(GetAction(this()),"10"))) SetAction("10");
  if(GreaterThan(Var(0),88)) if(LessThan(Var(0),100))  if(Not(SEqual(GetAction(this()),"20"))) SetAction("20");
  if(GreaterThan(Var(0),76)) if(LessThan(Var(0),89))  if(Not(SEqual(GetAction(this()),"30"))) SetAction("30");
  if(GreaterThan(Var(0),64)) if(LessThan(Var(0),77))  if(Not(SEqual(GetAction(this()),"40"))) SetAction("40");
  if(GreaterThan(Var(0),52)) if(LessThan(Var(0),65))  if(Not(SEqual(GetAction(this()),"50"))) SetAction("50");
  if(GreaterThan(Var(0),40)) if(LessThan(Var(0),53))  if(Not(SEqual(GetAction(this()),"60"))) SetAction("60");
  if(GreaterThan(Var(0),28)) if(LessThan(Var(0),41))  if(Not(SEqual(GetAction(this()),"70"))) SetAction("70");
  if(GreaterThan(Var(0),16)) if(LessThan(Var(0),29))  if(Not(SEqual(GetAction(this()),"80"))) SetAction("80");
  if(GreaterThan(Var(0),0))  if(LessThan(Var(0),17))  if(Not(SEqual(GetAction(this()),"90"))) SetAction("90");
  return(1);
