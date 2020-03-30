Hit:
  Sound("bottle");
  return(1);

Activate:
  //Sound("Firecast.wav");
  DoEnergy(15,Par(0));
  CreateObject(GL3A);
  RemoveObject();
  return(1);

check:
  if(Contained()) Call("Furz");
  return(1);

Furz:
  SetOwner(GetOwner(Contained()));
  //if(FindContents(HE3A,Contained())) Call("Ignorierdas");
  //if(Equal(GetOCF(Contained()),OCF_Living())) Sound("KnightMunch")
    //if(LessThan(GetEnergy(Contained()),50)) Sound("bottle")
       //Call("Activate");
  return(1);

Ignorierdas:
  return(1);