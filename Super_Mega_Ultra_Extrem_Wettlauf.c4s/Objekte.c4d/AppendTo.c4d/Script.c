/*-- Neues Objekt --*/

#appendto CLNK

protected func ControlSpecial2()
{
  [Neustart|Image=_DIE]
  if(!GameCall("DontMove"))
    Selbstmord();
  return(1);
}


protected func Death()
{
  SetAlive(1);
  DoEnergy(50000);
  MakeCrewMember(this(),GetOwner());
  ChangeDef(MEN1);
  this()->ChangeDef(CLNK);
  this()->SetAction("Walk");
  GameCall("RelaunchPlayer",GetOwner());
  return(1);
}

Initialize:
  SetPhysical("Energy",50000,2);
  SetPhysical("Breath",50000,2);
  SetPhysical("Walk",70000,2);
  SetPhysical("Jump",40100,2);
  SetPhysical("Swim",60000,2);
  SetPhysical("CanDig",0,2);
  SetPhysical("CanConstruct",0,2);
  SetPhysical("CanScale",0,2);
  SetPhysical("CanHangle",0,2);
  SetAction("Walk");
  SetDir(1);
  return(1);

Incineration:
  Extinguish();
  return(1);

Stop:
  SetPhysical("Walk",0,2);
  SetPhysical("Jump",0,2);
  SetComDir(COMD_None(), Var(0));
  return(1);

Resume:
  SetPhysical("Walk",70000,2);
  SetPhysical("Jump",40100,2);
  return(1);

Destroy:
  if(GetAction() eq "Ride"||GetAction() eq "RideStill")
    return(ObjectCall(GetActionTarget(),"Destroy"));
  CastObjects(BLUT, 20, 20);
  CastObjects(MEAT, 1, 20);
  return(Verschwinde());

Selbstmord:
  if(GetAction() eq "Ride"||GetAction() eq "RideStill")
    return(ObjectCall(GetActionTarget(),"Verschwinde"));
  if(Contained())
    ObjectCall(Contained(),"Verschwinde");
  else
    Verschwinde();
  return(1);

Verschwinde:
  if(GetAction() eq "Ride"||GetAction() eq "RideStill")
    return(ObjectCall(GetActionTarget(),"Verschwinde"));
  GameCall("RelaunchPlayer",GetOwner());
  return(1);
