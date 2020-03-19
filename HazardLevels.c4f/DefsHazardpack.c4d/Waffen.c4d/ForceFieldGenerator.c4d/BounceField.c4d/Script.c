/*-- Kraftfeld --*/

/* Wird erstellt. Par(1) ist Zielobjekt. */
public Launch:
  SetAction("Exist",Par(1));
  SetOwner(-1);
  //SetSolidMask(230,0,46,46);
  MunUpdate();
  return(1);
  
/* Kraftfeld-Aktion */
public CheckField:
  if(Contained())
    return(1);
  MunUpdate();
  if(Not(GetActionTarget())) return(RemoveObject());
  SetPosition(GetX(GetActionTarget()),GetY(GetActionTarget()));
  while(SetVar(0,FindObject(0, -24,-24,48,48,0,0,0,NoContainer(),Var(0)))) Repel(Var(0));
  SetVar(1,500);
  SetLocal(0,Local(0)+1);
  if(Local(0)>Var(1))
    return(Disable());
  if(Local(0)>Var(1)*3/4)
    return(SetDir(3));
  if(Local(0)>Var(1)/2)
    return(SetDir(2));
  if(Local(0)>Var(1)/4)
    return(SetDir(1));
  return(1);

Repel:
  if( GetOwner(Par(0))==GetOwner(Contained(GetActionTarget()))&&Contained(GetActionTarget()) )
    return(1);
  if(Par(0)==GetActionTarget())
    return(1);
  if(GetMass(Par(0))>=200)
    return(1);
  if(!(GetCategory(Par(0)) & C4D_Object()||GetCategory(Par(0)) & C4D_Living()))
    return(1);
  if(GetID(Par(0))==_HGG||GetID(Par(0))==_HG2)
    return(1);
  SetVar(1,Sub(GetX(),GetX(Par(0))));
  SetVar(2,Sub(GetY(),GetY(Par(0))));
  if(GetID(Par(0))!=ST5B||!Random(5))
    DoEnergy(-1,Par(0));
  Fling(Par(0),0,-10);
  SetSpeed(-Var(1)*2,-Var(2)*2-10,Par(0));
  if(SEqual(GetAction(Par(0)),"Travel")) {
    SetLocal(0,-Var(1)*2,Par(0));
    SetLocal(1,-Var(2)*2,Par(0));
    if (Local(0,Par(0))<0) SetDir(DIR_Left(),Par(0));
    else SetDir(DIR_Right(),Par(0));
  }
  if(ObjectCall(Par(0),"IsProjectile"))
    SetOwner(GetOwner(Contained(GetActionTarget())),Par(0));
  return(1);

public Disable:
  ObjectSetAction(GetActionTarget(),"Idle");
  RemoveObject();
  return(1);

MunUpdate:
  ObjectCall(GetActionTarget(),"EnergyUpdate",Contained(GetActionTarget()),(500-Local(0))*100/500);
  return(1);