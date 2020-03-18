/*-- Feuerblume --*/

#strict
#include PRNT

local Fireball, delay;

protected func Initialize()
{
	Fireball = 1;
	delay=10;
	SetAction("Lit");
}

Check:
  SetAction("Delay");
  return(1);

protected func Activate(pClonk)
{
	if (Fireball == 0)
		return 1;
	else 
	{
		Sound("smb3_fireball");
		var x;
		x = -4 + 8 * GetDir(pClonk);
		SetVar(0,CreateContents(_MFB));
		Exit(Var(0),0,-2,0,x,0,40);
		SetOwner(GetOwner(),Var(0));
		Fireball=0;
		delay+=delay/10;
		Schedule("Fireball=1", delay);
	}
}

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) DamageIt(Var(0));
  return(1);
  
DamageIt:
  Incinerate(Par(0));
  Hit();
  return(1);

public func Hit() {
  CastObjects(DFL2, 15, 20);
  Sound("Inflame");
  Sound("Fuse");
  RemoveObject();
}