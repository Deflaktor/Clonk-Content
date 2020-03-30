#strict

local user,partner,isdummy,entr,ttl,farbr,farbri,abslevel,durchg,saugdelay;

public func Activate(pcaller,pcaller2)
{
SetAction("Menu");
if(pcaller2)
	pcaller=pcaller2;
user=pcaller;
CreateMenu(GetID(),pcaller);
if(FindBase(GetOwner(pcaller)))
	AddMenuItem ("Wurmloch zur nächsten eigenen Basis öffnen","warpzu",FLAG,pcaller,0,1,"Öffnet ein Wurmloch zur nächsten eigenen Basis"); 
if(FindFriendlyBase(GetOwner(pcaller)))
	AddMenuItem ("Wurmloch zur nächsten befreundeten Basis öffnen","warpzu",FLAG,pcaller,0,5,"Öffnet ein Wurmloch zur nächsten befreundeten Basis"); 
AddMenuItem ("Wurmloch irgendwohin öffnen","warpzu",GetID(),pcaller,0,2,"Öffnet ein Wurmloch irgendwo in der Landschaft"); 
if(NextCrewMember(GetOwner(user)))
	AddMenuItem ("Wurmloch zum nächsten eigenen Mannschaftsmitglied öffnen","warpzu",CLNK,pcaller,0,3,"Öffnet ein Wurmloch zum nächsten eigenen Mannschaftsmitglied"); 
if(NextFriendlyMember(GetOwner(user)))
	AddMenuItem ("Wurmloch zum nächsten befreundeten Mannschaftsmitglied öffnen","warpzu",CLNK,pcaller,0,4,"Öffnet ein Wurmloch zum nächsten befreundeten Mannschaftsmitglied"); 
return(1);
}

func warpzu(stuff,iziel){
//var iziel;
var wohinx,wohiny;
if(iziel==1)
	{wohinx=GetX(FindBase(GetOwner(user))); wohiny=GetY(FindBase(GetOwner(user)));}
if(iziel==2)
	{wohinx=Random(LandscapeWidth()); wohiny=Random(LandscapeHeight());}
if(iziel==3)
{
if(Var()=NextCrewMember(GetOwner(user)))
	{wohinx=GetX(Var()); wohiny=GetY(Var());
		return(letsfetz(wohinx,wohiny));}
}

if(iziel==4)
{
if(Var()=NextFriendlyMember(GetOwner(user)))
	{wohinx=GetX(Var()); wohiny=GetY(Var());
		return(letsfetz(wohinx,wohiny));}
}

if(iziel==5)
{
if(Var()=FindFriendlyBase(GetOwner(user)))
	{wohinx=GetX(Var()); wohiny=GetY(Var());
		return(letsfetz(wohinx,wohiny));}
}

return(letsfetz(wohinx,wohiny));}



public func letsfetz(x,y)
{
//Log("x %d y %d",x,y);
var pzielwurm;
Sound("wormhole");
pzielwurm=CreateConstruction(GetID(),x-GetX(),y-GetY(),GetOwner(user),100);
Var()=CreateConstruction(GetID(),GetX(user)-GetX(),GetY(user)-GetY(),GetOwner(user),100); 
ObjectSetAction(Var(),"wachs",pzielwurm);
pzielwurm->dummy(Var());
RemoveObject();
return(1);
}
 
//^^
//=======================================

private func NextCrewMember(usr)
{
while(Var()=FindObject(0,0,0,-1,-1,OCF_CrewMember(),0,0,NoContainer(),Var()))
	if(GetOwner(Var())==usr)
		if(Var()!=user)
	 		 return(Var());
}

private func NextFriendlyMember(usr)
{
while(Var()=FindObject(0,0,0,-1,-1,OCF_CrewMember(),0,0,NoContainer(),Var()))
	if(!Hostile(GetOwner(Var()),usr))
		if(Var()!=user&&GetOwner(Var())!=usr)
	  		return(Var());
}

private func FindFriendlyBase(usr)
{
while(Var()=FindObject(0,0,0,-1,-1,OCF_Fullcon(),0,0,0,Var()))
	if(!Hostile(usr,GetOwner(Var())))
		if(GetBase(Var())!=-1)
			if(GetBase(Var())!=usr)
				return(Var());
return();
}

//========================================

public func dummy(ppartner)
{
isdummy=1;
partner=ppartner;
SetAction("wachs");
}

private func shrink()
{
DoCon(-1);
if(entr)
	{entr=0; SetEntrance();}
}

private func grow()
{
DoCon(+3);
if(!entr&&!isdummy&&GetCon()>299)
	{entr=1; SetEntrance(1);}
if(GetCon()>=300)
	SetAction("RotateMe");
}


private func FindPartner()
{
if(!isdummy)
	return(1);
if(partner)
	return(1);
Rem();
}

protected func Collection2(wer)
{
if(isdummy)
	return(Exit(wer));
if(GetOCF(wer)&OCF_CrewMember())
	Sound("warp");
Enter(GetActionTarget(),wer);
}

func kreis()
{
if(SEqual(GetAction(),"Menu"))
	return();

if(!FindPartner())
	return();

if(ttl++>1000)
	Rem();


if(!farbri)
	if(farbr++>80)
		farbri=1;
if(farbri)
	if(farbr--==0)
		farbri=0;

/*

if(GetCon()<299)
	return(CreateParticle ("PxSpark",0,0,0,-10,150,RGB(255,255,255)));

*/

if(durchg++==3){
	durchg=0;
	if(abslevel++>25)
		abslevel=0;}

if(isdummy)
	for(var i;i<=360;i=i+2)
		{
		CreateParticle ("PxSpark",Cos(i,5+(GetCon()/10)),Sin(i,5+(GetCon()/10)),Cos(i),Sin(i),100,RGBa(farbr,0,0,0)); 
		CreateParticle ("PxSpark",Cos(i,5+(GetCon()/10)-(abslevel-25)-1),Sin(i,5+(GetCon()/10)-(abslevel-25)-1),Cos(i),Sin(i),100,RGBa(Random(255),Random(155),Random(255),125)); 
		}

if(!isdummy)
{
	if( FindObject(_ZM4) ) saug();
	for(var i;i<=360;i=i+2)
		{
		CreateParticle ("wolke",Cos(i,1+(GetCon()/10)),Sin(i,1+(GetCon()/10)),-Cos(i,2),-Sin(i,2),50,RGBa(25,25,25,50)); 
		//CreateParticle ("wolke",Cos(i,1+(GetCon()/10)-abslevel-1),Sin(i,1+(GetCon()/10)-abslevel-1),-Cos(i,2),-Sin(i,2),50,RGBa(Random(155),Random(255),Random(255),125)); 
		}
}
}

func Rem(){
Sound("Magic1");
RemoveObject();
//SetAction("schrumpf");
}

Destruction:
if(isdummy)
	partner->Rem();
return();

private func saug()
{
if(GetAction() ne "RotateMe")
	return();

var distx,disty;

while(Var()=FindObject(0,-30,-30,60,60,OCF_Collectible(),0,0,NoContainer(),Var()))
	{
	if(GetX(Var())>GetX())
		SetXDir(+3,Var());
	if(GetX(Var())<GetX())
		SetXDir(-3,Var());
	if(GetY(Var())>GetY())
		SetXDir(+6,Var());
	if(GetY(Var())<GetY())
		SetXDir(-6,Var());
	
	if( ObjectDistance( Var() )<=6)
		Enter(this(),Var()); 

}



}
