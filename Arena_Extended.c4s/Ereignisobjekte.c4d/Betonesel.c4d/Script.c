/*-- Neues Objekt --*/

#strict

Initialize:
  SetOwner(-1);
  return(1);


public Hit:
  Sound("HolyDonkeyImpact");
  Explode(60,CreateObject(PRNT,-39));
  if(Equal(GetMaterial(0,10),Material("Granite"))) 
  if(Not(Random(5)))
  Explode(100);
  SetYDir(-35);
  SetXDir(0);
  return(1);

