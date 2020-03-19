#strict

Initialize:
  SetAction("10");
  return(1);

FixPos:
  SetVar(0,GetCursor(GetOwner()));
  SetVisibility(VIS_Owner());
  if(!Var(0))
    RemoveObject();
  SetPosition(GetX(GetCursor(GetOwner(this()))),Sub(GetY(GetCursor(GetOwner(this()))),17),this());
  return(1);

CheckEnergy:
  if(Not(Contained(GetCursor(GetOwner(this()))))) {
    //SetVar(0, GetEnergy(GetCursor(GetOwner())) );
    //SetVar(1, GetPhysical("Energy",0,GetCursor(GetOwner()))/1000 );
	Var(0)=Local(1,GetCursor(GetOwner()));
    Var(1)=1000;
    SetVar(0, Var(0)*100/Var(1) );
    SetLocal(3,Var(0));
  }
  if(Contained(GetCursor(GetOwner(this()))))
    SetVar(0, ( (GetDamage(Contained(GetCursor(GetOwner())))-600)*-1) * 100 / 600 );

  if(GetID(GetCursor(GetOwner(this())))==__DV)
    SetVisibility(VIS_None());
  else
    SetVisibility(VIS_All());
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
