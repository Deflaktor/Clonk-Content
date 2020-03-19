#strict

Dmg:
  return(3*15/8);

Initialize:
  return(SetAction("Fly"));

Start:
  SetXDir(Cos(GetR(),60));
  SetYDir(Sin(GetR(),60));
  return(1);

Check:
  if(GBackSolid()) RemoveObject();
  return(1);

Timer:
  BlastObjects(GetX(),GetY(),3);
  SetClrModulation(RGBa(255,255,255,Local(1)*17));
  if(Equal(Local(1),15)) RemoveObject();
  SetLocal(1,Sum(Local(1),1));
  return();

