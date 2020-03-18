#strict

Initialize:
  SetAction("Justify");
  return(1);

Setup:
  if(GetXDir()>0)
    SetAction("RotateRight");
  else
    SetAction("RotateLeft");
  return(1);

protected Hit:
  RemoveObject();
  CreateObject(KACX,0,0,-1);
  return(1);

