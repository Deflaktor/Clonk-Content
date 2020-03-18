//Locals  0Owner   1KI   2Counter
#strict

Initialize:
  SetOwner(-1);
  SetPosition(0,0);
  Local(0)=30;
  SetAction("Count");
  return(1);

Count:
  if(Local(0)<=0)
    return(Go());
  if(Local(0)>9) {
    Message(Format("Göttliche Vergeltung in 0:%d", Local(0)));
  } else {
    Message(Format("Göttliche Vergeltung in 0:0%d", Local(0)));
    Sound("BIP2",1);
  }
  Local(0)--;
  return(1);

Go:
  MusicLevel(10);
  Local(0)=10;
  Sound("Chor",1);
  Message("Göttliche Vergeltung!!!");
  for(var i = 0; i<50; i++) {
    SetPosition(Random(LandscapeWidth()),-10 - Random(1000),CreateObject(KAC5,0,0,-1));
  }
  SetAction("Remove");
  return(1);

Lautstarke: 
  Local(0)+=10;
  MusicLevel(Local(0));
  if(Local(0)>=(100-GameCall("MusicVolume")))
    RemoveObject();
  return(1);

