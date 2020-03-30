//Author wie immer Major aber das hier liest ja eh niemand also was solls}

#strict

local zauber1,zauber2,zauber3,count;

Initialize:
SetAction("wait");
return(1);

Hit:
Sound("WoodHit*");
CastObjects(SPRK,3,10,0,-3);
return(1);

private func getcomboval()
{
var val;
val=GetValue(0,zauber1)+GetValue(0,zauber2)+GetValue(0,zauber3);
return(val);
}

private func setcombo(id)
{
if(count==1)
zauber1=id;
if(count==2)
zauber2=id;
if(count==3)
zauber3=id;
if(count<3)
  return(setcombomenu());
count=0;
Message("Benötigte Zauberenergie für Kombos:%d",this(),getcomboval());
CloseMenu(Contained());
return(1);
}

private func setcombomenu(stuff,stuff2,easteregg) //*g*
{
if(easteregg&&!IsNetwork())
	if(ObjectCount(GOLD, -19, -19, 38, 38)==1&&ObjectCount(LOAM, -19, -19, 38, 38)==7) 
		return(ee());


CloseMenu(Contained());
count=count+1;

CreateMenu(MCMS,Contained(),0,3,"*ERROR*",GetMagicEnergy(),0,1);

while (Var(1)=GetPlrMagic(GetOwner(Contained()),0,Var(0)++)) 
    AddMenuItem( "%s als Combo setzen...", "setcombo",Var(1),Contained());    

return();
}



private func delcombo()
{
Sound("click");
count=0;
zauber1=0;
zauber2=0;
zauber3=0;
CloseMenu(Contained());
return(1);
}

private func docombo()
{
if(getcomboval()>GetMagicEnergy())
{
Message("Nicht genug Zauberenergie (benötigt:%d)",this(),getcomboval());
Sound("error");
return();
}
DoMagic(zauber1);
DoMagic(zauber2);
DoMagic(zauber3);
return(1);
}

IsZauberstab:
return(1);

recharge:
if(GetMagicEnergy()>99)
  return();
if (Not(DoMagicEnergy(+1))) return(0);
return(1);

Incineration:
SetAction("Burn");
return(1);

Burned:
if(!OnFire())
	return();
//Log("brenn");
Sound("Electric");
Sound("Discharge");
CastObjects(SPRK,30,50,2,-3);
DoMagicEnergy(+30);
while(GetMagicEnergy()>10)
{
DoMagicEnergy(-10);
LaunchLightning(GetX(),GetY(),Random(25)-Random(25), Random(10)-Random(10),Random(20)-Random(20),Random(10)-Random(10));
}


RemoveObject();
return(1);


private func cont(iopt)	//Manaenergie von Träger stehlen....
{
if(!Contained(iopt)||GetMagicEnergy()>99)
   return();
if(!GetMagicEnergy(Contained(iopt))){
	if(!iopt)
		return();
	return(cont(Contained()));}

while(GetMagicEnergy()<100&&GetMagicEnergy(Contained(iopt)))
	{DoMagicEnergy (+1); 
	DoMagicEnergy (-1,Contained(iopt));}

return(1);
}

protected ContentsCheck:
if(cont())
	return(Sound("Electric"));

if(GetMagicEnergy()>90)
  return();
  if (SetVar(0,FindContents(CRYS,Contained(this())))) ConvertCrystal(Var());
    return(1);

/* Energiegewinnung */

private ConvertCrystal:
  if (Not(DoMagicEnergy(+10))) return(1);
  
  RemoveObject(Par());
  
  Sound("Electric");
  return(1);


//von MagieClonk

public Activate: 
  [Zaubern|Image=MCMS]
  SetComDir(COMD_Stop(),Par(0));
  // Menü öffnen
  SetOwner(GetOwner(Par()));
  CreateMenu(MCMS,Par(),0,3,"Keine Zaubersprüche verfügbar",GetMagicEnergy(),0,1);


if(zauber1==0&&zauber2==0&&zauber3==0)
AddMenuItem( "Kombos setzen", "setcombomenu",_ZM1,Par());
else
{
AddMenuItem( "Kombos einsetzen", "docombo",_ZM2,Par());
AddMenuItem( "Kombos löschen", "delcombo",_ZM3,Par());
}
  while (Var(1)=GetPlrMagic(GetOwner(Par()),0,Var(0)++)) 
    AddMenuItem( "Zaubern: %s", "DoMagic", Var(1),Par());    
 SelectMenuItem(Local(),Par());
  return(1);

 
  

  
public DoMagic: // C4ID idSpell
SetLocal(0,GetMenuSelection(Contained()));
CloseMenu(Contained());
  // Nicht genug Zauberenergie
  if (GetMagicEnergy()<Value(Par(0)) )
    return( Message("Nicht genug|Zauberenergie!",this()), Sound("Error") );
     
CastObjects(SPRK,20,25,2,-3);

  // Aktion setzen
  
  // Zauberobjekt erschaffen und aktivieren
  if (!ObjectCall(CreateObject(Par(0),0,0,GetOwner()),"Activate",Contained()) )
    // Zauber fehlgeschlagen
    return(0);
  // Zauberenergie abziehen
  DoMagicEnergy(Value(Par(0))*(-1));
  // Fertig
  return(1); 


public LightningStrike:
if(GetMagicEnergy()>90)
  return();

  // Clonk soll anhalten
  if(Contained())
	SetComDir(COMD_Stop(),Contained());
  // Energiegewinnung
  DoMagicEnergy(+10);
  // Sound
  Sound("Electric");
  return(1);

Damage:
if(GetOCF()&OCF_OnFire()&&!SEqual(GetAction(),"Burn"))
	Incineration();
return();

public func IsAnvilProduct() {return(1);}
public func GetResearchBase() {return(HTZ0);}

//für ZauberKI

global func Hostileto(x,y,obj)
{
if(x!=y)
	if(x==-1||y==-1)
		//if(ObjectCall(obj,"IsEnemy"))
			return(1);
return(Hostile(x,y));
}

public func Zauberpack_Version()
{
return(199);
}

private func ee()
{
count=0;
Sound("Applause");
SetMatAdjust (RGB(150,100,100)); 
SetSkyAdjust(RGBa(12,12,255,127), RGB(255,255,0));
SetPlrViewRange (9999, Contained()); 

Var()=Contained();
Exit();
Enter(this(),Var());
SetPosition(100,100);
SetPlrView (GetOwner(Contained()), this()); 
SetRDir(300);

SetAction("ThanksTo",Contained());


}

private func eee()
{
count+=1;
if(count<=660)
	CastParticles("MSpark", 10,100, 0,0, 100, 200, RGBa(128,128,255,0), RGBa(255,255,255,127));

if(count==10)
	{Message("@Du hast also das Easteregg herausgefunden!");}

if(count==200)
	{Message("@Was soll ich nun mit dir machen?");}

if(count==400)
	{Message("@Am Besten erzähle ich dir, wer für dieses wunderschöne(*g*) Zauberpaket verantwortlich ist...");}

if(count==600)
	{Message("Folge mir einfach!");}

//if(count==658)
	//SetGamma (); 
if(count==659)
	{ //DrawMaterialQuad ("Sky",GetX(),GetY(),GetX()+100, GetY(), GetX()+100, GetY()+100, GetX(), GetY()+100);
	DrawMaterialQuad ("Earth",GetX(),GetY()+90,GetX()+100, GetY()+90, GetX()+100, GetY()+100, GetX(), GetY()+100);
	Local(1)=CreateObject(CLNK,10); Local(2)=CreateObject(CLNK,30); Local(3)=CreateObject(CLNK,80);
	SetDir(DIR_Right(),Local(1));
	SetDir(DIR_Left(),Local(2));
	SetVisibility(VIS_None(), Local(3)); SetRDir(10);}

//if(count==660)	
	//ResetGamma ();

if(count==780)
	Message("AlaNonna: Mach doch mal ein Zauberpack!",Local(1));

if(count==900)
	Message("Major(ich): OK!",Local(2));

if(count==1100)
	Message("Ala Nonna: Gut ^^",Local(1));

if(count==1300)
	Message("Ala Nonna: Worauf wartest du?",Local(1));

if(count==1400)
	Message("Major: Ich brauch nen Grafiker!",Local(2));

if(count==1500)
	Message("Ala Nonna: Hmm...",Local(1));

if(count==1600)
	Message("Major: Hmmmmmm...",Local(2));

if(count==1700)
	Message("Major:ICH BRAUCH NEN GRAFIKER!!!",Local(2));

if(count==1800)
	{CastParticles ("wolke", 10, 100, GetX(Local(3))-GetX(), GetY(Local(3))-GetY(), 30, 40, RGB(255,255,255), RGB(127,127,127)); 
	SetVisibility(VIS_All(), Local(3));
	SetDir(DIR_Left(),Local(3));
	Sound("Magic1");
	}

if(count==1900)
	{SetDir(DIR_Right(),Local(2));
	Message("Huch!",Local(2));
	}

if(count==2000)
	Message("kumopen: Hier bin ich!",Local(3));

if(count==2100)
	Message("major: Machst du die Images?",Local(2));

if(count==2200)
	Message("kumopen: Ja, unter der Bedingung, dass das Zauberpack von nun an Zauberpacket heißt...",Local(3));

if(count==2400)
	Message("major:kk!",Local(2));

if(count==2480)
	Message("kumopen: ...und es heißt nicht 'Images' sondern 'Bilder'...",Local(3));


if(count==2610)
	Message("major: grr! ;)",Local(2));

if(count==2700)
	Message("kumopen: Hier sind die Bilder!",Local(3));

if(count==2800)
	Message("major: Danke!",Local(2));

if(count==2880){SetDir(DIR_Left(),Local(2));
	Message("major: Ala, du als mein Betatester, hast du noch Fehler entdeckt...?",Local(2));}

if(count==3000)	
	Message("Ala Nonna: JA! Sehr viele! Also die Effekte und also...",Local(1));
if(count==3100)	
	Message("Ala Nonna: ... das ist ja...",Local(1));
if(count==3200)	
	Message("Ala Nonna: und die Fehler erst und und und!",Local(1));
if(count==3300)	
	Message("Ala Nonna: bla bla bla bla",Local(1));
if(count==3500){Sound("Boing");
	Message("major: *Hilfe*",Local(2));}
if(count==3580)
	SetDir(DIR_Right(),Local(2));

if(count==3600)
	Message("major: kumopen, ich glaube wir können veröffentlichen!",Local(2));

if(count==3800){Sound("Trumpet");
	Message("kumopen: *g*",Local(3));}

if(count==4000)
	Message("@Vielen Dank an:|Ala Nonna, treuer Betatester und Clonker er immer gegen mich gewinnt :/|kumopen für die wirklich guten Grafiken|dem channel #clonkscript inklusive Insassen für die Hilfe!|und natürlich mir selbst für meine große Geduld ;)");


if(count==4050)
	Sound("Applause");


if(count==4400)
	Message("So liebe Leute! Das war die Geschichte des Zauberpakets!| Ich hoffe ihr habt so viel Spaß damit wie ich ;-)");


if(count==4600){
for(var i;i<=30+Random(30);i++)
	{Var()=CreateObject(GOLD,Random(LandscapeWidth())-GetX(),RandomX(-200,-2000)-GetY(),-1);
	SetGraphics (0, Var(), FLNT);} //*gg* Ich muss den Leuten doch mal nen Schrecken einjagen ^^


	Exit(Contents()); SetAction("wait"); count=0; RemoveObject(Local(1)); RemoveObject(Local(2)); RemoveObject(Local(3));}



	



	
}





