Initialize:
  return(SetAction("Fly"));

Start:
  SetXDir(Cos(GetR(),100));
  SetYDir(Sin(GetR(),100));
  return(1);

Check:
  if(GBackSolid()) RemoveObject();
  return(1);

Timer:
  if(Equal(Local(1),10)) RemoveObject();
  SetLocal(1,Sum(Local(1),1));
  return();