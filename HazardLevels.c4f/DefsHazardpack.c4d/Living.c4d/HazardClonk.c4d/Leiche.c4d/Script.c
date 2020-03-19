#strict

Initialize:
  SetAction("Death");
  SetPhase(1);
  return(1);

Meldung:
  Sound("Die");
  DeathAnnounce();
  return(1);

Damage:
  if(!Global(0))
    return(1);
  if(GetDamage()>30&&OnFire()) {
    SetPhase(0);
    Extinguish();
    DoDamage(-30);
  }
  if(GetPhase()==0)
    CastObjects(BL7L,Par(0),Par(0)+10);
  else
    CastObjects(BL7K,Par(0),Par(0)+10);
  if(GetDamage()>50&&!Local(0))
    Platzen();
  return(1);

Platzen:
  if(!Global(0))
    return(1);
  if(GetPhase()==0)
    CastObjects(BL7L,80,Par(0)+10);
  else
    CastObjects(BL7K,80,Par(0)+10);
  if(GetPhase()==1) {
    CastObjectsX(MEAT,1,Par(0)+20,0,0,270,90,false);
    SetPhase(2);
  }
  RemoveObject();
  SetLocal(0,1);
  return(1);

Incineration:
  if(GetPhase()!=1||!Global(0))
    Extinguish();
  return(1);