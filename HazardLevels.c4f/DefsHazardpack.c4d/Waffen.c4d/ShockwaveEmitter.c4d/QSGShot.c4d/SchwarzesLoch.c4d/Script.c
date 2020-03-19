#strict

local destroyLandscapeRadius, dontDieYet;

DestroyingBlackHole:
  return(GameCall("DestructableLandscape"));

Initialize:
SetAction("Blast");
return(1);

CheckSog:
if (GetMaterial(GetX(Par(0)),GetY(Par(0)))==Material("Earth"))
return(1);
//if (BitAnd(OCF_CrewMember(),GetOCF(Par(0))))
Jump(Par(0));
SetVar(1,Sub(GetX(),GetX(Par(0))));
SetVar(2,Sub(GetY(),GetY(Par(0))));
SetSpeed(Div(Var(1),2),Div(Var(2),2),Par(0));
if(SEqual(GetAction(Par(0)),"Travel")) {
  SetLocal(0,Div(Var(1),2),Par(0));
  SetLocal(1,Div(Var(2),2),Par(0));
}
if(DestroyingBlackHole()&&(GetCategory(Par(0))==1||GetCategory(Par(0))==2) && destroyLandscapeRadius>=100) {
  if(Var(1)/20==0)
    Var(1)=20*Var(1)/Abs(Var(1));
  if(Var(2)/20==0)
    Var(2)=20*Var(2)/Abs(Var(2));
  SetPosition(GetX(Par(0))+Var(1)/20,GetY(Par(0))+Var(2)/20,Par(0));
  dontDieYet=1;
}
return(1);

Activity:
SetLocal(3,Sum(Local(3),1));
if ((Local(3)>=150&&!dontDieYet)||Local(3)>200)
  return(Remove());
dontDieYet=0;

destroyLandscapeRadius+=2;
var radius = GetCon()*destroyLandscapeRadius/100;

if(DestroyingBlackHole()&&destroyLandscapeRadius<=95&&destroyLandscapeRadius % 8) {
  var ecken = BoundBy(8 + 8*radius/100 - 6*radius*radius/100000,8,36);
  VieleckZeichnen("Earth", radius, ecken);
}
if(DestroyingBlackHole()&&destroyLandscapeRadius==100)
  VieleckZeichnen("Earth", GetCon(), 72);

DigFree(GetX(),GetY(),Min(GetCon()+10, radius+10));

while(SetVar(0,FindObject(0,-1*GetCon(),-1*GetCon(),2*GetCon(),2*GetCon(),0,0,0,NoContainer(),Var(0))))
  if(GetCategory(Var(0)) & C4D_Object()||GetCategory(Var(0)) & C4D_Living()||GetCategory(Var(0)) & C4D_Vehicle() || DestroyingBlackHole())
    if(!SEqual(GetProcedure(Var(0)),"ATTACH") || DestroyingBlackHole())
      if(GetID(Var(0))!=_HGG || DestroyingBlackHole())
        CheckSog(Var(0));

while (SetVar(1,FindObject(0,-25,-30,50,60,0,0,0,0,Var(1))))
  if (Not(Equal(Var(1),this())))
{
  if (GetID(Var(1))==_SLC||GetID(Var(1))==_QSG)
  {
    //CastParticles("FSpark", Random(40),100, 0,0, (Random(40)+2000), 150, RGBa(255,255,0,0), RGBa(255,127,0,255));
    Sound("Energize");
    destroyLandscapeRadius=BoundBy(destroyLandscapeRadius,40,90);
    RemoveObject(Var(1));
    SetLocal(3,Local(3)-20);
    DoCon(GetCon(Var(1))/2);
    SetXDir();
    SetYDir();
    return(1);
  }  

  if(!(GetCategory(Var(1)) & C4D_Object()||GetCategory(Var(1)) & C4D_Living()||GetCategory(Var(1)) & C4D_Vehicle()) && !DestroyingBlackHole())
    return(1);

  if(SEqual(GetProcedure(Var(1)),"ATTACH") && !DestroyingBlackHole())
    return(1);

  if(ObjectCall(Var(1),"Delete"))
    return(1);

  if(GetOCF(Var(1)) & OCF_CrewMember())
    return(Kill(Var(1)));
  
  if(GetID(Var(1))==_HGG && !DestroyingBlackHole())
    return(1);

  if(GetID(Var(1))==__DV)
    return(1);

  Sound("Saug");
  CreateParticle("PxSpark",0,6,0,0,150,RGBa(100,100,180,100));
  RemoveObject(Var(1));
}
return(1);

Remove:
ObjectCall(CreateObject(SW4V),"Init",GetCon());
return(RemoveObject());


VieleckZeichnen:
  var material = Par(0);
  var radius = Par(1);
  var ecken = BoundBy(Par(2), 3, 360);
  var x = GetX() + Par(3);
  var y = GetY() + Par(4);
  var underground = 1;
  for (var winkel = 0; winkel<360; winkel+=360/ecken) {
    var x1, x2, y1, y2;
    x1 = x + Sin(winkel, radius);
    y1 = y + Cos(winkel, radius);
    if(GetMaterial(x1 - GetX(), y1 - GetY())==Material("Sky"))
      underground = 0;
  }
  for (var winkel = 0; winkel<360; winkel+=360/ecken) {
    var x1, x2, y1, y2;
    x1 = x + Sin(winkel, radius);
    y1 = y + Cos(winkel, radius);
    x2 = x + Sin(winkel+360/ecken, radius);
    y2 = y + Cos(winkel+360/ecken, radius);
    DrawMaterialQuad(material,x,y,x1,y1,x2,y2,x,y,underground);
  }
  return(1);