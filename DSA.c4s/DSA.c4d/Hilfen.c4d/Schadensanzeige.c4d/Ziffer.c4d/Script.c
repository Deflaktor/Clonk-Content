/*-- Neues Objekt --*/

#strict

local alpha;

Initialize:
  return(1);

Set:
  SetAction("Show");
  SetPhase(Par(0));
  return(1);

Go:
  SetPosition(GetX(),GetY()-2);
  //DoCon(-4);
  SetClrModulation(RGBa(255,255,255,alpha));
  alpha=BoundBy(alpha+10,0,255);
  if(alpha>250)
    RemoveObject();
  return(1);