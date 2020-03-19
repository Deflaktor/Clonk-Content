#strict

Initialize:
  An();
  return(1);

Damage:
if(GetAction()S="Kaputt")
return(1);
  CastObjects(SHRD,40,20,0,0);  
  Sound("Discharge");
  Sound("GlassBreak");
  SetAction("Kaputt");
  if(Local())
  RemoveObject(Local(0));
  return(1);

Flacker:
  if(Not(Random(15))) And(CastObjects(SU3V,Sum(1,Random(1)),Sum(5,Random(15)),Sum(-14,Random(28)),Sum(1,Random(2))),Sound("Spark*"));
  if(Not(Random(2))) return(0);
  if(Random(6)) return(ObjectSetAction(Local(0),"Neon")&&SetAction("FlackerAn"));
  if(Random(6)) return(ObjectSetAction(Local(0),"Aus")&&SetAction("FlackerAus"));
  return(1);

Energie:
  if(GetAction()S="Kaputt")
  return(1);
  if (Not(GameCall("MainEnergySupply", this()))) return(Aus());
  if (GameCall("MainEnergySupply", this())) return(An());
  return(0);

An:
  if(Local(0)) return(1);
  SetAction("An");
  ObjectSetAction(Local(0)=CreateObject(LJ3V,-20,16),"Neon");
  return(1);

Aus:
  SetAction("Aus");
  if(Local(0)) RemoveObject(Local(0));
  return(1);