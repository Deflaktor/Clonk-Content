Initialize:
  SetAction("0Beere");
  return(1);

RejectCollect:
  return(1);

ControlDig:
  SetLocal(0,Par(0));
  while(Contents())  Enter(Local(0),Contents());
  SetAction("0Beere");
  return(1);

Wachsezu1:
  if(Equal(Random(3),1)) Call("Eins");
  return(1);
Eins:
  CreateContents(EB3A);
  SetAction("1Beere");
  return(1);

Wachsezu2:
  if(Equal(Random(3),1)) Call("Zwei");
  return(1);
Zwei:
  CreateContents(EB3A);
  SetAction("2Beere");
  return(1);

Wachsezu3:
  if(Equal(Random(3),1)) Call("Drei");
  return(1);
Drei:
  CreateContents(EB3A);
  SetAction("3Beere");
  return(1);

Wachsezu4:
  if(Equal(Random(3),1)) Call("Vier");
  return(1);
Vier:
  CreateContents(EB3A);
  SetAction("4Beere");
  return(1);

Wachsezu5:
  if(Equal(Random(3),1)) Call("Fuenf");
  return(1);
Fuenf:
  CreateContents(EB3A);
  SetAction("5Beere");
  return(1);

finito:
  RemoveObject();
  return(1);