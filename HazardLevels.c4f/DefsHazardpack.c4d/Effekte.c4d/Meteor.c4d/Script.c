#strict

SmokeTrail:
  Smoke(0,0,5);
  Smoke(0,-5,Random(7));
  return(1);
Completion:
  SetAction("Evaporate");
  return(1);
Hit:
  ObjectCall(CreateObject(EXPL),"Launch",10+Random(12));
  RemoveObject();
  return(1);
