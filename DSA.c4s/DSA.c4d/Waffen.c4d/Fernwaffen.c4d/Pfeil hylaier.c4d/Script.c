Hit:
  if(SEqual(GetAction(),"Shot")) Call("Exloperre");
  return(1);

InFlight:
  if(SetLocal(0,FindObject(0,-20,-20,40,40,OCF_Living(),0,0,NoContainer())))
    if(Not(Equal(Local(0),Local(1))))  Hit();
  if(Local(2)==2) CreateObject(_TRS);
  return(1);

Exloperre:
  CastObjects(HF3A, 15, 25);
  Sound("PengKlirr");
  Explode(10*Local(2));
  return(1);