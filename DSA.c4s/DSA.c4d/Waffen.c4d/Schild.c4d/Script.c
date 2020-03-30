/*-- Schild --*/

// Schild wird angelegt
Activate:
  if (Not(Equal(GetID(Contained()),KR3A))) return(0);
  Sound("Connect");
  SetOwner(GetOwner(Contained()));
  ChangeDef(SHIA);
  SetAction("Shield",Contained());
  return(1);

CPUtest:
  if(Equal(GetID(Contained()),KS3A)) Call("hopphopp");
  if(Equal(GetID(Contained()),KA3A)) Call("hopphopp");
  if(Equal(GetID(Contained()),KB3A)) Call("hopphopp");
  if(Equal(GetID(Contained()),K13A)) Call("hopphopp");
  if(Equal(GetID(Contained()),K23A)) Call("hopphopp");
  if(Equal(GetID(Contained()),K33A)) Call("hopphopp");
  if(Equal(GetID(Contained()),K43A)) Call("hopphopp");
  if(Equal(GetID(Contained()),K53A)) Call("hopphopp");
  if(Equal(GetID(Contained()),K63A)) Call("hopphopp");
  return(1);

hopphopp:
  SetOwner(GetOwner(Contained()));
  ChangeDef(SHIA);
  SetAction("Shield",Contained());
  return(1);

Hit:
  Sound("MetalHit*");
  return(1);
