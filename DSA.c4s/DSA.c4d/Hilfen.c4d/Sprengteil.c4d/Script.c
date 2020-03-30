Check:
  if(Not(Equal(Local(2),2))) SetYDir(30);
  if(FindObject(0,-7,-7,14,14,OCF_Living(),0,0,NoContainer())) Call("Hit");
  return(1);

Hit:
  Explode(5);
  return(1);

Initialize:
  SetAction("Baaaaaaaaaaffffff");
  return(1);