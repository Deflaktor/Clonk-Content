/*-- Sägemehl --*/
#strict

protected Initialize:
  SetAction("Dust");
  SetPhase(Random(4));
  return(1);

protected Timer:
  if (!Random(10)) Remove();
  return(1);

public Launch:
  if(!Global(0)) return(2);
  if(Par(0)==0) CastObjects(BL7K,20,20);
  return(1);

Remove:
  Hit();
  RemoveObject();
  return(1);

Hit:
  if(Global(0)==2&&!Random(20)) {
    CastPXS("Blood", 1, 0);
    RemoveObject();
  }
  return(1);