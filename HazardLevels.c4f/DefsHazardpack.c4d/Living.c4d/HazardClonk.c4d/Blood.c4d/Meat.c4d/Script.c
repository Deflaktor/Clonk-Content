#strict

protected Initialize:
  SetAction("Decay");
  return(1);

protected Remove:
  CastObjects(BL7K,20,20);
  RemoveObject();
  return(1);

Decaying:
  DoCon(-4);
  if(GetCon()>50)
    return(1);
  CastObjects(BL7K,5,5);
  RemoveObject();
  return(1);

protected Hit:
  // Sound("MeatHit");
  CastObjects(BL7K,20,20);
  SetXDir(-2);
  SetRDir(2);
  return(1);

Bluten:
  if(GetXDir()!=0)
    CastObjects(BL7K,1,5);
  return(1);

protected Damage:
  CastObjects(BL7K,Par(0),Par(0)+10);
  Local(0)++;
  if(GetDamage()>30&&Par(0)>10&&Local(0)>3)
    Remove();
  return(1);