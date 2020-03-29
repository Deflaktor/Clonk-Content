/*-- Superkuppel --*/

#strict

protected func Initialize()     // Initialisierung
{
  SetCategory(C4D_StaticBack());
  // Airlocks erzeugen wenn noch nicht da
  if(!FindObject(AIRL,-190,100))
    CreateConstruction(AIRL,-190,105,GetOwner(),100,1)->AIRL::SetLeft();
  if(!FindObject(AIRL,+190,100))
    CreateConstruction(AIRL,+190,105,GetOwner(),100,1)->AIRL::SetRight();

  // Wasser abpumpen
  SetAction("Pump");
}

DamageRedirect:
  Damage(Par(0)*2, Par(1), Par(2));
  return(1);

Damage:        // Schaden weitergeleitet vom Stopper-Helfer
  // Zerstörung bei zuviel Damage
  if(Par(0)>=140-GetDamage()/100) {
    CastObjects(SHRD,30,100,0,-50);
    CastObjects(_TF1,10,90,0,-50);
    CastObjects(_TF2,20,100,0,-50);
    Sound("DomeDestruct");
    ChangeDef(SPDD);
	if(Local(0))
      RemoveObject(Local(0));
	if(Par(2))
	  RemoveObject(Par(2));
  }
  return(1);

protected func Transfer()       // StartCall von Pump
{
  // Wasser absaugen
  for(var i=0;i<300;++i) {
    if(ExtractLiquid(0,99)==-1) {
      return(1);
    }
  }
}

/* Callbacks */

public func IsDeepSeaResearch() { return(1); }

public func GetResearchBase() { return(FSTW); }
