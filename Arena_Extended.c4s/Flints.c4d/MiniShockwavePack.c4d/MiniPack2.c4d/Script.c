#strict
#include PRNT

/* Zufallsflint */
Redefine:
  if(Contained())
    while(ScrollContents(Contained())!=this()) {}
  return(1);

Hit:
  for(var i=0;i<8;i++)
    CastObjectsX(HNTF,4,50+Random(50),0,-10-Random(10),270,180,"Sett");
  Explode(30);
  return(1);

Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

Sett:
  ObjectSetAction(Par(0),"Checking");
  SetOwner(GetOwner(), Par(0));
  return(1);