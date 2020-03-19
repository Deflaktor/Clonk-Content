Initialize:
  return(SetOwner(-1));

Activate:
Aufplatzen();
return(1);

Zeit:  
  if(InLiquid()) return(Aufplatzen());
  SetLocal(0,Sum(Local(0),1));
  if (GreaterThan(Local(0),100)) return(Stippel());
  return(1);

Stippel:
  if(Not(Frei()))                              return(0);
  if(Contained())                              return(0);
  if(FindObject(0,-10,-10,20,20,OCF_OnFire())) return(0);
  
  if(Not(FindObject(KG5B)))
    if(Local(0,FindObject(ST5_))<=5) return(Koenigin());
  
  if(Not(FindObject(KG5B)))
    if(Not(Random(15))) return(Koenigin());
  
  if(Global(1))
    if(Not(Random(16))) return(Miffelbaum());

  if(Global(2))
    if(Not(Random(8))) return(Moff());

  ObjectCall(CreateObject(ST5B),"Frisch");

  Sound("STKokon");
  return(RemoveObject());

DoppelStippel:
  if(Not(Frei()))                              return(0);
  if(Contained())                              return(0);
  if(FindObject(0,-10,-10,20,20,OCF_OnFire())) return(0);
  

  if(ObjectCount(KG5B)<Global(3))
    if(Local(0,FindObject(ST5_))<=5) return(DKoenigin());
  
  if(ObjectCount(KG5B)<Global(3))
    if(Not(Random(15))) return(DKoenigin());
  
  if(Global(1))
    if(Not(Random(16))) return(DMiffelbaum());

  if(Global(2))
    if(Not(Random(8))) return(DMoff());

  ObjectCall(CreateObject(ST5B),"Frisch");

  Sound("STKokon");
  CreateObject(SK5B);
  return(RemoveObject());

Koenigin:
  return(Miffelbaum());

Miffelbaum:
  if(Not(Global(1)))                   return(0);
  if(Not(ObjectCount(KG5B)))           return(0);
  if(FindObject(MB5B,-50,-50,100,100)) return(0);
  if(Not(GBackSolid(0,3)))             return(0);
  CreateConstruction(MB5B,0,5,-1,10);
  Sound("STKokon");
  return(RemoveObject());

DMoff:
  if(Not(Global(2)))                   return(0);
  CreateObject(MF5B);
  Sound("STKokon");
  CreateObject(SK5B);
  return(RemoveObject());

DKoenigin:
  return(DMiffelbaum());

DMiffelbaum:
  if(Not(Global(1)))                   return(0);
  if(Not(ObjectCount(KG5B)))           return(0);
  if(FindObject(MB5B,-50,-50,100,100)) return(0);
  if(Not(GBackSolid(0,3)))             return(0);
  CreateConstruction(MB5B,0,5,-1,10);
  Sound("STKokon");
  CreateObject(SK5B);
  return(RemoveObject());

Moff:
  if(Not(Global(2)))                   return(0);
  CreateObject(MF5B);
  Sound("STKokon");
  return(RemoveObject());


Frei:
  return(Not(GBackSemiSolid()));

Hit:
  return(Sound("RockHit*"));

Damage:
  return(Aufplatzen()); 

Activate:
  return(Aufplatzen()); 

Incineration:
  return(Aufplatzen()); 

Aufplatzen:
  CastObjects(FZ5B,10,50);
  RemoveObject();
  return(1);
