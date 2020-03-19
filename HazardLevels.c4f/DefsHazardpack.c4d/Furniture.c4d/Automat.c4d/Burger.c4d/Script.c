#strict

Activate:
  Message("Hmmm! Das BSE schmeckt man garnicht raus!",Contained());
  Sound("Munch");
  DoEnergy(+50,Contained());
  RemoveObject();
  return(1);
