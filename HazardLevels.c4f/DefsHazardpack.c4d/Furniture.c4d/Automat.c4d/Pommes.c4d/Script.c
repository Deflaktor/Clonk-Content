#strict

Activate:
  Message("Hm. Jetzt hab ich durst!",Contained());
  Sound("Munch");
  DoEnergy(+50,Contained());
  RemoveObject();
  return(1);
