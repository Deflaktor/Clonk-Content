Initialize:
  SetAction("Close");
  return(1);

SetDirRight:
SetDir(1);
  return(1);

SetDirLeft:
SetDir(0);
  return(1);

CheckOpen:
  while(Var(0)=FindObject(BIK1,-40,20,80,60,0,0,0,NoContainer())) return(Open());
return(1);

Open:
SetSolidMask(90,77*GetDir(),90,77,0,0);
SetAction("Open");
  return(1);

Close:
SetSolidMask(0,77*GetDir(),90,77,0,0);
SetAction("Close");
  return(1);