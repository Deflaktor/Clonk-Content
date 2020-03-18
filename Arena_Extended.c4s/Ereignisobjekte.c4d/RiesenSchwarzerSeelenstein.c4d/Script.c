/*-- Tür --*/
#strict

Initialize:
  SetOwner(-1);
  return(1);

Incineration:
  Extinguish();
  return(1);

Hit:
  Sound("Frag3.wav");
  PutSolidMask();
  return(1);

PutSolidMask:
  SetSolidMask(0,0,28,38);
  return(1);

Damage:
  if ( LessThan( GetDamage(), 70 ) ) return(0);
  if (GetAction() S= "Idle") {
    SetAction("Delay");
    SetOwner(Par(1));
  }
  return(1);

Blast:
  CastObjects(S582,10,100);
  CastObjects(S582,10,100,10);
  CastObjects(S582,10,100,10,10);
  CastObjects(S582,10,100,0,10);
  Explode(200);
  Sound("Discharge");
  Sound("Blast2");
  return(1);

Destroy:
SetWealth(Par(0),GetWealth(Par(0))+200);
return(0);