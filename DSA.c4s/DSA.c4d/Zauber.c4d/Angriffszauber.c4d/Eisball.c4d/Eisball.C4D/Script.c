//Author:major}

#strict

local owner,oldx,newc;

private func CastMe()
{
  if (GetComDir() == COMD_Left()) CastLeft();
  if (GetComDir() == COMD_Right()) CastRight();
}

private func CastRight()
{  SetLocal(0,+50);
  SetPosition(GetX()+20,);
   SetPlrView (owner,this()); 
  SetAction("Travel");
}

private func CastLeft()
{
  
  SetLocal(0,-50);
  SetPlrView (owner,this());
  SetPosition(GetX()-20,);
  SetAction("Travel");
}

func Activate()
{
 newc=10;
 oldx=-1;
 owner=GetOwner(Par());
  SetLocal(2,GetY());
  if (GetDir(Par(0))==DIR_Left()) SetComDir(COMD_Left());
  if (GetDir(Par(0))==DIR_Right()) SetComDir(COMD_Right());
  Sound("Magic1");
  CastMe();
  return(1);}


protected func Hit()
{
Sound("Crystal*");
CastParticles ("MSpark",10,20,0,0,12,100,RGBa(0,0,255,0),RGBa(50,50,205,50)); 
RemoveObject();
}

private func Travel()
{ if(oldx==GetX()&&newc--<=0)
	return(Hit());
SetRDir(20);
//Log("oldx %d getx %d",oldx,GetX());
  oldx=GetX();
  SetXDir(Local(0));
  CreateParticle ("MSpark",0,0,0,-10,190,RGBa(20,20,200,50)); 
  //CreateParticle ("wolke",0,0,GetXDir(),-10,190,RGBa(20,20,Random(200),50));
  CastParticles ("PxSpark",20,60,0,0,38,52,RGBa(20,20,200,50),RGBa(100,100,255,50)); 
  SetPosition(GetX(),Local(2));
 
  if(Var()=FindObject(0,-12,-13,24,26,OCF_Living(),0,0,NoContainer(),Var()))
	if(GetAlive(Var()))
	{Sound("freeze"); CreateObject(_FLB,0,25)->go(Var()); DoEnergy(-15,Var()); return(Hit());}
  return(1);
}