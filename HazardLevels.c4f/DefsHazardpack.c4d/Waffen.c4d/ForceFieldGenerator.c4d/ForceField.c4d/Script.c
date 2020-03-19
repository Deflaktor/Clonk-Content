/*-- Kraftfeld --*/
#strict

/* Wird erstellt. Par(1) ist Zielobjekt. */
public Launch:
  SetAction("Exist",Par(1));
  MunUpdate();
  return(1);
  
/* Kraftfeld-Aktion */
public CheckField:
  if(Not(GetActionTarget())) return(RemoveObject());
  ForcePosition(this(),GetX(GetActionTarget()),GetY(GetActionTarget()));
  if(GreaterThan(GetDamage(),79)) return(Disable());
  if(GreaterThan(GetDamage(),60)) return(SetDir(3));
  if(GreaterThan(GetDamage(),40)) return(SetDir(2));
  if(GreaterThan(GetDamage(),20)) return(SetDir(1));
  return(1);

Damage:
  MunUpdate();
  return(1);

MunUpdate:
  ObjectCall(GetActionTarget(),"EnergyUpdate",Contained(GetActionTarget()),100-100*GetDamage()/80);
  return(1);

public Disable:
  ObjectSetAction(GetActionTarget(),"Idle");
  RemoveObject();
  return(1);
