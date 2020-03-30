#strict

Activate:
Sound("Energize");
SetOwner(-1);

if(!GetDir(Par()))
	{SetAction("Field2");
	SetPosition(GetX()-50,GetY()+15);
	SetSolidMask (0, 46,90,46); 
	return();}
SetPosition(GetX()+50,GetY()+15);
SetAction("Field1");
return(1);
    
private func Destroy()
{
  Sound("DeEnergize");
  RemoveObject();
  return(1);
}
  
private func CheckIdle()
{
  if (ActIdle()) RemoveObject();
  return(1);
}
