/*-- Tür --*/

Initialize:
  SetAction("SetColor");
  return(1);

SetMyColor:
  if(GetOwner()==-1)
    SetColorDw(RGBa(255, 255, 255, 0));
  if(GBackSolid(-7,23)||GBackSolid(7,23)) Hit();
  return(1);

Incineration:
  Extinguish();
  return(1);

Hit:
  PutSolidMask();
  return(1);

PutSolidMask:
  SetSolidMask(0,0,48,48);
  return(1);

Damage:
  if ( LessThan( GetDamage(), 70 ) ) return(0);
  if (GetAction() S= "Idle") {
    SetAction("Delay");
	if(GetOwner()==-1)
      SetOwner(Par(1));
  }
  return(1);

Blast:
   for(var i = 0; i<50; i++)
{
  SetVar(0,CreateObject(WBOB,0,0,GetOwner()));
  Var(0)->SetMyColor();
  ObjectSetAction(Var(0),"Setting");
  SetSpeed(Sub(Random(400),200),Sub(Random(400),350),Var(0));
}
  RemoveObject();
  Sound("Blast2");
  return(1);