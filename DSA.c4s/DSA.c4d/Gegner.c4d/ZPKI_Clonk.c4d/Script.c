#strict
#include CLNK

local stab,target,flucht,ret,works,lastcmd;

public func IsWorking() {return(works);}
public func IsNotWorking() {return(!works);}


public func Initialize()
{
CreateObject(KS3A);
CreateObject(KA3A);
CreateObject(_G02);
CreateContents(HTZ0);
SetClrModulation (RGB(200,200,200));
if(!FindContents(HTZ0))
  	CreateContents(HTZ0);
if(!DefinitionCall(HTZ0,"IsZauberstab"))
	{Log("Zauberpack KI::ERROR-Zauberpack nicht geladen!");	while(Var()=FindObject(GetID())) RemoveObject(Var()); return();}

if(DefinitionCall(HTZ0,"Zauberpack_Version")<199)
	{Log("Zauberpack KI::WARNING-Zauberpack ist nicht aktuelle Version!");
	Log("Dies kann zu Fehlern führen. Bitte neueste Version vom CCAN downloaden.");}
  SetAction("Walk");
  SetDir(Random(2));
  return(1);
}


RejectCollect:
  return(1);

private func Activity()
{
DoMagicEnergy(1);
DoMagicEnergy(1);
DoMagicEnergy(1);
DoMagicEnergy(1);
DoMagicEnergy(1);
stab=FindContents(HTZ0);
if(!stab) //kein zauberstab
	return(nimmstab());//SetCommand (this(),"Aquire",0, 0, 0,0, HTZ0,3));

if(GetCon()<100)
	if(!Random(6))
		DoCon(+1);


if(!Random(8))
	target=FindNextTarget();

deadcheck();

if(!target){target=FindNextTarget();
   if(!target) 
	return(wasanderestun());}
   

if(target)
{
if(!flucht)
	{if(!GetCommand())
		//if(GetCon()<=109)
			SetCommand (0,"MoveTo",0,GetX(target)+vonseite(),GetY(target),0,0,10);
		//if(GetCon()>109) {Jump();
			//SetCommand (0,"Jump",0,GetX(target),GetY(target),0,0,3);}
	if(GetMagicEnergy()<30&&GetEnergy()<20)
		abhauen(target);
	}

if(GetEnergy()>40)
	if(flucht)
		flucht=0;
if(flucht&&!Random(5))
	Jump();


if(ObjectDistance(target)>700)
	{if(flucht)
		flucht=0;
	target=0;}

if(ObjectDistance(target)<30&&GetEnergy()>20&&!Random(7+ZPKI_rndzahl)&&ZPKI_dif>=1)
	SetCommand (this(),"Attack", target); //Dem Feind in die Fresse hauen 8)



throwit();

//Hier steht der code für das verhalten nach verwandlung, der leider unsinn war da die verwandelten clonks 
//den standart source des verwandelten feuermonster besitzen :(
/*
if(GetID()==HH05){  //Feuerspucken ^_^
	if(!Random(4)&&ObjectDistance(target)<100){
		ausrichten(target); ControlThrow();}
	if(!flucht) SetCommand (0,"MoveTo",0,GetX(target),GetY(target),0,0,10);}

if(GetID()==HH04){  //Schlangenbiss (,,)(,,)(,,):>
	if(!Random(2)&&ObjectDistance(target)<3)
		ControlThrow();
	if(!flucht) SetCommand (0,"MoveTo",0,GetX(target),GetY(target),0,0,10);}
*/


if(flucht)
	if(genug(HZA8)&&!Random(3+ZPKI_rndzahl/2)&&GetAction() ne "Jump")
		{zauber(HZA8);
		return();}


if(!flucht)
	if(!Random(4+ZPKI_rndzahl/2))
		if(Var()=FindObject(HZB5,-150,-150,300,300))
			SetCommand (this(),"Enter",Var(),0,0,0,0,5);

if(GetAction() eq "Swim"||GetAction() eq "Walk"||GetAction() eq "Jump")
	tuzaubern();

return(1);}
}


private func ActivateContents(pobj)
{
SetCommand(this(),"None");
ShiftContents(0,0,GetID(pobj)); 
}



private func deadcheck()
{
if(FindObject(_ZPS))
	if(Var()=FindObject(0,-240,-240,480,480,OCF_Living(),"Dead"))
		{if(ObjectDistance(Var())>75)
			SetCommand (this(),"MoveTo",Var(),0,0,0,0,5);
			if(ObjectDistance(Var())<=75)
			{DrawParticleLine ("wolke",0,0,AbsX(GetX(Var())),AbsY(GetY(Var())),5,50,RGBa(255,255,255,127),RGBa(0),-20);
			CastParticles("Smoke", 10,100, AbsX(GetX(Var())),AbsY(GetY(Var())), 100, 200, RGBa(255,0,Random(255),100), RGBa(0,255,Random(255),200));
			ChangeDef(ZPKI,Var()); SetOwner(GetOwner(),Var()); DoEnergy(100,Var()); Var()->Initialize(); if(!Random(7)) Var()->abhauen();}}
return(1);
}


private func tuzaubern()
{
var nr;

if(GetMagicEnergy(stab)<5)
	return();

//======================
//wichtige Zauber


if(genug(HZB0)&&OnFire())
	zauber(HZB0);


if(ZPKI_dif>=3){
if(genug(MGHL))
	if(GetEnergy()<20+Random(10))
		zauber(MGHL);}

//Antimagie bei Gift
if(genug(HZA7)&&FindObject(HZA5,-5,-5,10,10))
	zauber(HZA7);

if(!Random(13)&&genug(HZA7)&&ObjectEnemyCount(HZA5,GetOwner(),-100,-100,200,200))
	zauber(HZA7);



//Inhaltsobjekte löschen
if(ZPKI_dif>=2){
	if(genug(EXTG))
		for(var i;i<=ContentsCount();i++)
			if(OnFire(Contents(i)))
				zauber(EXTG);}


			


//if(div>=9){
//if(genug(HZB6)&&FindFriendlyObject(0,GetOwner(),-100,-100,200,200,0,"Dead",0,NoContainer()))
//	zauber(HZB6);}



//Gravitationsstoß
if(genug(HZB2)&&ObjectEnemyCount(0,GetOwner(),-100,-100,200,200,0,"Shot",0,NoContainer())&&!Random(3))
	zauber(HZB2);

if(!ret++>2+Random(1))
	return();
ret=0;

//======================

if(!Random(12+(ZPKI_rndzahl/2)))	
	return();

nr=RandomX(1,15);
//nr=4;
//Log("%d",nr);

//======================
//unwichtige Zauber danach return

if(ZPKI_dif>3){
if(nr==9&&!Random(3+ZPKI_rndzahl/2))
{if(genug(HTBX)&&ObjectDistance(target)>30&&ObjectDistance(target)<200){ausrichten(target);
	return(zauber(HTBX));}}}


/*
if(nr==2)
{if(genug(HHZ1)&&ObjectDistance(target)<50&&GetCon()<=109){ausrichten(target);  //Wachstum
	return(zauber(HHZ1));}}*/
if(ZPKI_dif>5){
if(nr==3) //Schutzschild
if(genug(MFFS)&&!FindObject(FRCS,-2,-2,4,4)&&FindObject(HTM2)&&!Random(5+ZPKI_rndzahl)||genug(MFFS)&&ObjectDistance(target)<100&&!FindObject(FRCS,-2,-2,4,4)&&!Random(13)||genug(MFFS)&&flucht&&!FindObject(FRCS,-2,-2,4,4)&&!Random(10))
	return(zauber(MFFS));}

if(nr==4||nr==8) //Manaschuss bzw Meteor
{if(genug(HTM9)&&Random(30-ZPKI_rndzahl)&&ObjectDistance(target)<300&&Inside(GetY(target),GetY()-45,GetY()+45)&&PathFree (GetX(), GetY(),GetX(target),GetY(target)))
	{ausrichten(target);
	if(genug(HTM3)&&!Random(3))
		return(zauber(HTM3));
	if(genug(HTM9))
		return(zauber(HTM9));}}

if(ZPKI_dif>3){
if(nr==5&&!Random(12)) //Blenden
  if(genug(HZB4)&&ObjectDistance(target)<120)
	return(zauber(HZB4));}


if(ZPKI_dif>=7){
if(nr==6&&!Random(10)) //Gift HZA5
	if(genug(HZA5)&&ObjectDistance(target)<220)
		return(zauber(HZA5));}
if(ZPKI_dif>2){
if(nr==7)
	if(genug(HZB2)&&ObjectEnemyCount(0,GetOwner(),-200,-200,400,400,0,"Jump",0,NoContainer()))
	return(zauber(HZB2));}

if(ZPKI_dif>5){
if(nr==10)
	if(genug(HTM2)&&ObjectDistance(target)>20+Random(35)&&ObjectDistance(target)<200+Random(35))
		return(zauber(HTM2));}

if(ZPKI_dif>=8){
if(nr==11&&!Random(20))
	if(genug(HTM2)&&ObjectDistance(target)>20+Random(35)&&ObjectDistance(target)<200+Random(35))
		return(zauber(HTM2));}

if(nr==12||nr==13)
	if(genug(HHZ6))
		if(ObjectEnemyCount(HH02,GetOwner(),-100,-100,200,200)||ObjectEnemyCount(HH03,GetOwner(),-100,-100,200,200)||ObjectEnemyCount(HH04,GetOwner(),-100,-100,200,200)||ObjectEnemyCount(HH05,GetOwner(),-100,-100,200,200)||ObjectEnemyCount(HH06,GetOwner(),-100,-100,200,200))
			return(zauber(HHZ6));

/*
if(nr==14&&genug(HHZ5)&&GetID()==ZPKI&&!Random(10))
	return(zauber(HHZ5));

if(nr==15&&genug(HHZ4)&&GetID()==ZPKI&&!Random(10))
	return(zauber(HHZ4));
*/

//======================

}



private func vonseite()
{
if(GetX()<GetX(target))
	return(RandomX(-10,-150));
return(RandomX(10,150));
}

private func ausrichten(auf)
{
if (GreaterThan(GetX(auf),GetX())) ControlLeft();  
if (LessThan(GetX(auf),GetX())) ControlRight();
return(1);
}

private func abhauen(vor)
{
flucht=1;

ausrichten(vor);
  // Bewegungskommando
  SetVar(0,-1); if (Equal(GetDir(),DIR_Right())) SetVar(0,+1);
  SetCommand(this(),"None");
  AddCommand(this(),"MoveTo",0,Sum(GetX(),Mul(100,Var(0))),GetY(),0,20);
  SetLocal(1,1,FindObject(KT3A,-200,-100,400,200));
  SetLocal(1,1,FindObject(_GTT,-200,-100,400,200));
return(1);
}


private func FindNextTarget()
{
while(Var()=FindObject(0,-500,-500,1000,1000,OCF_CrewMember(),0,0,0,Var()))
	if(Hostileto(GetOwner(),GetOwner(Var()))){SetCommand(this(),"None");
		return(Var());}
return();
}

/*global func Hostileto(a,b)
{
if(a==-1||b==-1)
	if(a!=b)
		return(1);
return(Hostile(a,b));
}
Unnötig da bereits in Zauberpack integriert!
*/

private func genug(id)
{
if(GetMagicEnergy(stab)-GetValue(0,id)>=0)
	return(1);
return();
}

private func zauber(id)
{
return(ObjectCall(stab,"DoMagic",id));
}

	
//Alter Mist
private func nimmstab()
	{Var()=FindObject(HTZ0,-1,-1);
	if(!Var())
		{Var(1)=FindBase(GetOwner());
			if(!Var(1))
				return();
		SetCommand (this(),"Aquire",0, 0, 0,0, HTZ0,3); return();}
	
	if(ObjectDistance(Var())<1000)
		return(SetCommand (this(),"Get",Var()));


}



protected func Death()
{
  CreateObject(_AB1);
  Sound("Die");
  GibErfahrung();
  Message("Ihr habt gewonnen!",this(),GetName());
  Log("BOT_DIE: %s",GetName());
  Explode(50);
  return(1);
}

GibErfahrung:
  var obj; 
  while (obj=FindObject(0, -500,-200,1000,400, OCF_CrewMember(), 0,0, NoContainer(), obj)) 
    DoCrewExp(GetValue(0,GetID()),obj);
  return(1);


global func ObjectEnemyCount(id,owner,x,y,h,w,ocf,act,actt,container){ //liefert Anzahl Objekte eines feindlichen Spieler in einem best. Radius
while(Var()=FindObject(id,x,y,h,w,ocf,act,actt,container,Var()))
	if(Hostileto(GetOwner(Var()),owner))
		Var(1)=Var(1)+1;
return(Var(1));}

global func FindFriendlyObject(id,owner,x,y,h,w,ocf,act,actt,container)
{
while(Var()=FindObject(id,x,y,h,w,ocf,act,actt,container,Var()))
	if(!Hostileto(GetOwner(Var()),owner))
		return(Var());
return(0);


}

func wasanderestun()
{
if(GetCommand()){lastcmd++; if(lastcmd>45) {SetCommand(this(),"None"); lastcmd=0;}
	return();}
//if(ContentsCount()>1)
	if(works==1)
		return(arbeiten());

if(!Random(7))
	return();




if(GetOwner()>-1)
	if(GetCursor(GetOwner())==this())
		return();

if(!Random(2)&&GetMagicEnergy(stab)<91)
	if(Var()=FindObject(CRYS,0,0,-1,-1))
		return(SetCommand(this(),"Get",Var()));	


if(GetOwner()>-1)
{
arbeiten();
return();
}

if(!Random(2))
	if(Var()=FindObject(HTZ0,0,0,-1,-1))
		return(SetCommand(this(),"Get",Var()));
return(SetCommand(this(),"MoveTo",0,Random(LandscapeWidth()),Random(LandscapeHeight())));

}

public func ReproductionX()
{
  if (GetCon()<100) return(0);
  Var(0)= CreateConstruction(GetID(),0,0,-1,40);
  ObjectCall(Var(0),"Initialize");																						  return(1);
}

public func IsTarget() {return(1);}

private func throwit()
{
if(GetAction() ne "Walk")
	return();
if(ZPKI_dif>=2){
	for(var i;i<=ContentsCount();i++){
		if(Contents(i)){
			if(GetID(Contents(i))!=FLNT)
			if(GetID(Contents(i))==BO5B||GetID(Contents(i))==TFLN||GetID(Contents(i))==EFLN){
				//Log("id von ex cont %s",GetName(Contents(i)));
				ausrichten(target);
				ActivateContents(Contents(i));
				AddCommand (this(),"Throw");
				if(!Random(5))
					abhauen();
				}
			if(GetID(Contents(i))==CWBO){
				if(GetAction(Contents(i)) eq "Counting")
					{SetCommand (this(),"Throw");
					return(abhauen(Var()));}

				if(ObjectDistance(target)<200)
					Contents(i)->Activate();
				ausrichten(target);
				ActivateContents(Contents(i));
				AddCommand (this(),"Throw",0,GetX(target),GetY(target));
				}
			if(GetID(Contents(i))==FLNT||GetID(Contents(i))==SFLN){
				ActivateContents(Contents(i));
				AddCommand (this(),"Throw",0,GetX(target),GetY(target));}
			}}




}// */

}

private func arbeiten()
{
if(Var()=FindBase(GetOwner()))
	if(ObjectDistance(Var())<1000)
		//if(GetPathLength(GetX(),GetY(),GetX(Var()),GetY(Var()) )!=0)
			Var(2)=1;
if(!Var(2))
	return();




for(var i;i<=ContentsCount(0,this());i++) 
	{if(Var(1)=Contents(i))
		{
		if( GetID( Var(1) ) != HTZ0 )
			return(SetCommand (this(),"Put",Var(),0,0,0,GetID(Var(1)),1));
		}
	} 



if(Var(1)=FindFreeObject(0,0,0,-1,-1,OCF_Collectible(),0,0,NoContainer()))
	if(ObjectDistance(Var(1))<1000)
		SetCommand (this(),"Get",Var(1),0,0,0,0,3);
			
}


public func ContextStartWork(pCaller)
{
  [Sammeln|Image=GOLD|Condition=IsWorking()]
  Message("Zu Befehl!",this());
  works=1;
  return(1);
}

public func ContextEndWork(pCaller)
{
  [Sammeln abbrechen|Image=_MN1|Condition=IsNotWorking()]
  Message("Zu Befehl!",this());
  works=0;
  return(1);
}

private func FindFreeObject()
{
Var(1)=FindObject(0,0,0,-1,-1,OCF_Collectible(),0,0,NoContainer());
if(!Var(1))
	return();
	

if( GetMaterial ( AbsX(GetX(Var(1))),AbsY(GetY(Var(1))) ) ==Material("Earth") ||  GetMaterial ( AbsX(GetX(Var(1)))),AbsY(GetY(Var(1)))  ==Material("Sand") ||  GetMaterial ( AbsX(GetX(Var(1))),AbsY(GetY(Var(1))) ) ==Material("Ashes")|| !GBackSolid (AbsX(GetX(Var(1)))),AbsY(GetY(Var(1))))
	return(Var(1));
return();
}