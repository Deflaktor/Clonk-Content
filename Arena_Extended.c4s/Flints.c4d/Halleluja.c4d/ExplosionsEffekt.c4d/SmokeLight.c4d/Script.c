/*-- Neues Objekt --*/

#strict

Initialize:
  SetPosition(GetX(), GetY()+67);
  SetAction("Justify");
  SetPhase(Random(10));
  return(1);

Setup:
  Local(0)=GetXDir();
  Local(1)=GetYDir();
  return(1);

Decelerate:
  Var(0)=1;
  if(Local(0)<0)
    Local(0)++;
  else
    Local(0)--;
  if(Local(1)<0)
    Local(1)++;
  else
    Local(1)--;
  SetSpeed(Local(0), Local(1));
  return(1);

Remove:
  RemoveObject();
  return(1);