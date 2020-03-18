/* Luftblase */

#strict

protected func Shiver()
  {
  SetXDir(Random(21)-10);
  if (!InLiquid()) Remove();
  return(1);
	}

protected func Initialize()
  {
  SetAction("Bubble");
  SetComDir(COMD_Up());
  return(1);
	}

protected func Remove()
  {
  RemoveObject();
  return(1);
  }
