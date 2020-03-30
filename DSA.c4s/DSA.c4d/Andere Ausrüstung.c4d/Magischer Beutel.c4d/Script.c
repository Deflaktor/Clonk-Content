Initialize:
  return(1);

ControlThrow:
  Exit(this(),0,3);
  return(1);

ControlDigDouble:
  if(Local(0))  GrabContents(Local(0));
  SetLocal(0,CreateObject(LB3A,Random(LandscapeWidth()),Random(LandscapeHeight())));
  while(Contents())  Enter(Local(0),Contents());

  Enter(Par(0));
  return(1);

ControlUp:
  if(Contained()) return(0);
  if(Local(0))  GrabContents(Local(0));
  if(Local(0))  RemoveObject(Local(0));
  SetLocal(0,0);
  Sound("Limbus.wav");
  return(1);
  

RejectCollect:
  if(Equal(Par(0),MB3A)) return(1);
  return(0);