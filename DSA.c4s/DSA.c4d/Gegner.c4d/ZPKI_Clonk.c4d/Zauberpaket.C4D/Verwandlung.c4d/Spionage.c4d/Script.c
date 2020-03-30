#strict

local olddw;

func Activate(ziel)
{
SetAction("waitX",ziel);
CreateMenu(GetID(), GetActionTarget() ,0,0,0,0,0); //"Keine anderen Spieler vorhanden"
for(var i;i<=GetPlayerCount();i++)
	if (GetPlayerName(i)&&i!=GetOwner(GetActionTarget())) 
		AddMenuItem( Format("Farbe von Spieler %d (%s) annehmen",i,GetPlayerName(i)) ,"ChangeColor" ,CLNK , GetActionTarget(),0,i);

}

private func ChangeColor(stuff,iplr)
{
if(Var()=FindObject(GetID(),0,0,0,0,0,"wait",GetActionTarget()))
	Var()->rem();
SetAction("wait");
olddw=GetColorDw (GetActionTarget());

//Var(1)=GetID( FindObjectOwner(0,iplr) );

//Var()=GetPlayerInfoCoreVal ("ColorDw", 0, iplr);
Var()=GetColorDw (FindObjectOwner(0,iplr,0,0,-1,-1,OCF_CrewMember())); 
//Log("%d",Var());
//Log("%d",iplr); 
SetColorDw (Var(), GetActionTarget()); 
CreateParticle ("wolke",0,0,0,-5,130,Var()); 
}

func rem()
{
Sound("Magic1");
CreateParticle ("wolke",0,0,0,-5,130,olddw); 
SetColorDw (olddw, GetActionTarget());
RemoveObject();
}

