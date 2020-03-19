/*-- Clustergrenade --*/

#strict
#include _AM5
#include _MOV

/* Aufschlag */
BlowUp:
  ObjectCall(CreateObject(EXPL),"Launch",DirectHitDamage()*2);
  CastObjects(_SPL,6,40,0,0);
  RemoveObject();
  return(1);

DirectHitDamage:
  return(5);
  
Dmg:
  return(DirectHitDamage()+DefinitionCall(_SPL, "Dmg")*6);

