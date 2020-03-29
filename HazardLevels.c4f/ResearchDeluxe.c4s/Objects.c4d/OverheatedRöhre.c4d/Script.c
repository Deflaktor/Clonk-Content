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

Overheat: 
  Aus();
  CastPXS("WeakMetal",1000,50,0,5);
  CastPXS("Earth",100,100,0,0);
  Explode(20,CreateObject(EXPL,-20,30));
  Explode(20,CreateObject(EXPL,20,30));
  Explode(30);
  return(1);
  
An:
  if(!Local(0)) {
    SetAction("An");
    ObjectSetAction(Local(0)=CreateObject(LJ3V,-20,16),"Neon");
	return(1);
  }
  if(!Local(1)) return(ObjectSetAction(Local(1)=CreateObject(LJ3V,-20,16),"Neon"));
  if(!Local(2)) return(ObjectSetAction(Local(2)=CreateObject(LJ3V,-20,16),"Neon"));
  if(!Local(3)) return(ObjectSetAction(Local(3)=CreateObject(LJ3V,-20,16),"Neon"));
  if(!Local(4)) return(ObjectSetAction(Local(4)=CreateObject(LJ3V,-20,16),"Neon"));
  if(!Local(5)) return(ObjectSetAction(Local(5)=CreateObject(LJ3V,-20,16),"Neon"));
  if(!Local(6)) return(ObjectSetAction(Local(6)=CreateObject(LJ3V,-20,16),"Neon"));
  if(!Local(7)) return(ObjectSetAction(Local(7)=CreateObject(LJ3V,-20,16),"Neon"));

  return(Overheat());

Aus:
  SetAction("Aus");
  if(Local(0)) RemoveObject(Local(0));
  if(Local(1)) RemoveObject(Local(1));
  if(Local(2)) RemoveObject(Local(2));
  if(Local(3)) RemoveObject(Local(3));
  if(Local(4)) RemoveObject(Local(4));
  if(Local(5)) RemoveObject(Local(5));
  if(Local(6)) RemoveObject(Local(6));
  if(Local(7)) RemoveObject(Local(7));
  return(1);