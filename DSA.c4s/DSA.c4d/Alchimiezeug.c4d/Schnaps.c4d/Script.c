Hit:
  Sound("bottle");
  return(1);

Activate:
  DoEnergy(5,Par(0));
  if(GetID(Par(0))!=KR3A&&GetID(Par(0))!=KRRA) {
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  DoMagicEnergy(-1,Par(0));
  }
  RemoveObject();
  return(1);