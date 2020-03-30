Initialize:
  return(1);

Checkoben:
  if(GreaterThan(Local(0),2))  if(SetLocal(1,FindObject(0,-7,-17,15,14,OCF_Living()))) Call("Schmechz");
  SetSolidMask(0,4,15,1,0,4);
  Call("Flach");
  return(1);

Checkunten:
  if(GreaterThan(Local(0),2))  if(SetLocal(1,FindObject(0,-7,-6,15,14,OCF_Living()))) Call("Schmechz");
  SetSolidMask(0,4,15,1,0,0);
  Call("Flach");
  return(1);

Checkrechts:
  if(GreaterThan(Local(0),2))  if(SetLocal(1,FindObject(0,-7,-7,14,15,OCF_Living()))) Call("Schmechz");
  SetSolidMask(16,0,1,15,0,0);
  Call("Stehend");
  return(1);

Checklinks:
  if(GreaterThan(Local(0),2)) if(SetLocal(1,FindObject(0,-16,-7,14,15,OCF_Living()))) Call("Schmechz");
  SetSolidMask(16,0,1,15,4,0);
  Call("Stehend");
  return(1);

Schmechz:
  SetDir(Random(2));
  Punch(Local(1),10);
  if(Random(2)) Sound("Hurt*");
  SetLocal(0,0);
  return(1);

Flach:
  SetVertex(0,0,  9 );
  SetVertex(0,1, -4 );
  SetVertex(1,0, -8 );
  SetVertex(1,1, -4 );
  return(1);

Stehend:
  SetVertex(0,0, -8 );
  SetVertex(0,1,  7 );
  SetVertex(1,0, -2 );
  SetVertex(1,1,  7 );
  return(1);


Test:
  if(LessThan(Local(0),5)) SetLocal(0,Sum(Local(0),1));
  if(Equal(Local(9),1)) SetAction("Spikesoben");
  if(Equal(Local(9),2)) SetAction("Spikesunten");
  if(Equal(Local(9),3)) SetAction("Spikesrechts");
  if(Equal(Local(9),4)) SetAction("Spikeslinks");
  return(1);