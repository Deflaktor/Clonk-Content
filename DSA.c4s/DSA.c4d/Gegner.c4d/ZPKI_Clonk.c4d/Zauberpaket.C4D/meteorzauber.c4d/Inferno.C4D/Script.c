//Author:MAJOR}

static old,oldb,cnt,lw,lh,i,cnsky;

#strict
Activate:
cnt=1400;
cnsky=1000;

if(!old){
old=GetSkyAdjust(); 
oldb=GetSkyAdjust(1); 
SetSkyAdjust(RGBa(255,180,180,127), RGB(180,0,0));
SetSkyParallax (SkyPar_Keep(),SkyPar_Keep(),SkyPar_Keep(),17);}


SetVar(0,40);
SetPosition(GetX(),0);

lw=LandscapeWidth();
lh=LandscapeHeight();

while(Var())

{


SetVar(10,CreateObject(METO,Random(1700)-Random(1700),-GetX()-50-Random(7000)));

if(!Random(7))
	CreateObject(RCK2,Random(1700)-Random(1700),-GetX()-50-Random(7000));

SetVar(1,Random(1));
if(GetX(Var(10))<GetX(Par()))
  SetXDir(30,Var(10));
if(GetX(Var(10))>GetX(Par()))
  SetXDir(-30,Var(10));
SetYDir(5,Var(10));

SetVar(0,Var()-1);
}

SetAction("wait");


ObjectSetAction(SetLocal(0,CreateObject(FRCS,0,0,GetOwner())),"Field",Par(0));

return(1);

check:
if(cnsky>0){
	for(i=0;i<(lw+lh)/2-Random((lw+lh)/2);i++)
		CreateParticle("MSpark", Random(lw)-GetX(), Random(lh)-GetY(),0,80, 30+Random(50),RGBa(255-Random(10),10-Random(10), 0,128));
	}
	if(cnsky--==0)
		oldsky();

if(!cnt--)
	Rem();
return();

private Rem:

   PrivateCall(Local(),"Destroy");
   RemoveObject();
  return(1);

private oldsky:

if(ObjectCount(GetID())>1)
	return();
SetSkyParallax(SkyPar_Keep(),SkyPar_Keep(),SkyPar_Keep()); 
SetSkyAdjust (old,oldb); 


old=0;
oldb=0;

return(1);
