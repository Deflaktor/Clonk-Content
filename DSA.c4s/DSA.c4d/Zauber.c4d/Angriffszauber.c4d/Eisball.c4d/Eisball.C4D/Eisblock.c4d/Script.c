#strict

local helper,ttl;

protected func go(ziel)
{
DoCon(-20);
ttl=100;
helper=CreateObject(_FLH,0,0,-1);
SetGraphics ( 0, helper, ( GetID( ziel ) ) ); 
if(ObjectCall(ziel,"IsClonk"))
	{ObjectSetAction(helper,"clonk",this());} //DoCon(-50,helper);}
if(!ObjectCall(ziel,"IsClonk"))
	ObjectSetAction(helper,"att",this());

Enter(helper,ziel);
SetClrModulation ( RGBa(150,150,230,200), helper ); 
return(1);
}

protected func ControlDown()
{
if(!Random(7))
	Message("Du bist eingefroren und kannst dich nicht bewegen O_O",helper);
return(1);
}

protected func check()
{
SetPosition(GetX(),GetY(),helper);
SetR(GetR(),helper);
if(!ttl--||GetMaterial()==Material("Lava"))
	return(shrink());
}

private func shrink()
{
CastPXS ("Water",3,3); 
ttl=100-(GetTemperature()/2);
DoCon(-1);
if(GetCon()<=70)
	return(Rem());
}

protected func Incineration()
{
return(Rem());
}

func Rem()
{
Sound("IceBreak");
RemoveObject(helper,1);
CastObjects (ICE1,2+Random(2),20); 
RemoveObject(0,1);
return(1);
}

protected func Hit()
{
SetPosition(GetX(),GetY()-1);
SetRDir(Random(hs()*15));
SetXDir(Random(hs()*7)-Random(hs()*7));
SetYDir(Random(hs()*15)-Random(hs()*5));
}

private func hs()
{

if(GetOCF()&OCF_HitSpeed4())
	return(10);

if(GetOCF()&OCF_HitSpeed3())
	return(7);

if(GetOCF()&OCF_HitSpeed2())
	return(4);

if(GetOCF()&OCF_HitSpeed1())
	return(2);

}
