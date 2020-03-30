#strict

#include _ZTE

Activate:
  SetLocal(0,Par(0));
  SetLocal(2,CalcPower(Local(0)));
  SetLocal(1,Random(6));
  SetAction("Countdown");
  Enter(Local(0));
  return(0);

Counter:
  if(GreaterThan(GetActTime(),300)) Call("fettisch");
  return(1);

Check:
  if(FindObject(0,-7,-7,14,14,OCF_Living(),0,0,NoContainer())) Hit();
  return(1);

Hit:
  if(SEqual(GetAction(),"Rain"))
    return(1);
  if(!Local(3))
    return(SetAction("Rain"));
  SetVar(1,CalcDamage(5,Local(2)));
  Explode(Var(1));
  return(1);

fettisch:
  Sound("DeEnergize");
  RemoveObject();
  return(1);

ElementWahl:
  if(Equal(Local(1),0)) return("Erz");
  if(Equal(Local(1),1)) return("Luft");
  if(Equal(Local(1),2)) return("Feuer");
  if(Equal(Local(1),3)) return("Humus");
  if(Equal(Local(1),4)) return("Wasser");
  if(Equal(Local(1),5)) return("Eis");

PourDown:
  SetVar(0,CreateObject(ZE3A,-30+Random(60),-35));
  ObjectSetAction(Var(0),ElementWahl()); 
  SetLocal(2,Local(2),Var(0));
  SetLocal(3,1,Var(0));
  SetYDir(Random(10),Var(0));
  SetXDir();
  SetYDir();
  if(GreaterThan(GetActTime(),(100+CalcPower(Local(0)))/2)) fettisch();
  while(SetVar(1,FindObject(0,-30,-35,60,35,OCF_Alive(),0,0,NoContainer(),Var(1)))) {
    SetYDir(100,Var(1));
    SetXDir(0,Var(1));
  }
  return(1);
