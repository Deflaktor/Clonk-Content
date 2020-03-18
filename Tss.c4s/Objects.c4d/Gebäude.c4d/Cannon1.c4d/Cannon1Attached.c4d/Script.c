/*--- Kampfgeschütz (angeschraubt) ---*/

#strict

local controller;

/* Überladbar für andere Kanonen */

protected func RotationSpeed() { return(5); }
protected func CannonMobileID() { return(CTW3); }
protected func CannonAmmo(object obj) { return(GetOCF(obj) & OCF_Collectible() ); }
protected func CannonPowderNeeded(object obj) { return(1); }
protected func CannonPower(object obj) { return(12); }
protected func CannonSound(object obj) { return("Blast3"); }
protected func CannonSmoke(object obj) { return(1); }

/* Turm weg? */

protected func AttachTargetLost()
{
  ComStopDouble();
}

/* Kommandos aus dem Turm */

public func ComLeft(object pClonk)
{
  SetAction("Rotating",GetActionTarget());
  SetRDir(-RotationSpeed() );
  return(1);
}

public func ComRight(object pClonk)
{
  SetAction("Rotating",GetActionTarget());
  SetRDir(RotationSpeed() );
  return(1);
}

public func ComStop(object pClonk)
{
  SetAction("Attaching",GetActionTarget());
  SetRDir(0);
  return(1);
}

public func ComStopDouble(object pClonk)
{
  var r = (GetR() + 270) % 360;
  SetR(r);
  ChangeDef(CannonMobileID() );
  return(1);
}

public func ComFire(object pClonk)
{
  SetAction("Attaching",GetActionTarget());
  SetRDir(0);
  controller = GetOwner(pClonk);
  CreateMenu(GetID(GetActionTarget()), pClonk, this(), 0, "$TxtNoammo$");
  
  var i, obj;
  while(obj = Contents(i++, GetActionTarget()) )
    if(GetID(obj) != GUNP)
      if(CannonAmmo(obj) )
        AddMenuItem(Format("$TxtShoots$",GetName(obj)), "Shoot", 0, pClonk, 0, obj, 0, 4, obj);
  return(1);
}

private func Shoot(id defFoo, object pObj)
{
  var powder = CannonPowderNeeded(pObj);
  if(ContentsCount(GUNP, GetActionTarget()) < powder)
  {
    Sound("Error");
    Message("$TxtNotenoughgunpowder1r$", GetActionTarget(), powder);
  }
  else
  {
    for(var i = 0; i < powder; ++ i)
      RemoveObject(FindContents(GUNP, GetActionTarget()) );

    if(CannonSmoke(pObj) )
    {
      Smoke(Sin(GetR(), 13), -Cos(GetR(), 13), 20);
      Smoke(Sin(GetR(), 18), -Cos(GetR(), 23), 17);
      Smoke(Sin(GetR(), 22), -Cos(GetR(), 32), 14);
      Smoke(Sin(GetR(), 25), -Cos(GetR(), 40), 11);
    }
    
    Exit(pObj, Sin(GetR(), 13), -Cos(GetR(), 13), GetR(), Sin(GetR(), CannonPower(pObj)), -Cos(GetR(), CannonPower(pObj)), 20);
    if(GetOCF(pObj) & OCF_CrewMember() ) ObjectSetAction(pObj, "Tumble");
    Sound(CannonSound(pObj) );
    SetPlrView(controller, pObj);
  }
}

