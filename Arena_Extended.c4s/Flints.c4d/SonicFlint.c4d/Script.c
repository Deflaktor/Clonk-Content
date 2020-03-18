#strict
#include PRNT

local turbo, boosts, x,y;

Check:
  SetAction("Delay");
  return(1);

Sign:
  if(Par(0)<0)
    return(-1);
  return(1);
  
Checkit:
  if(turbo<=0&&boosts<6) {
    if(!x)
      x=GetXDir();
    if(!y)
      y=GetYDir();
    SetXDir(GetXDir()+x);
    SetYDir(GetYDir()+y);
    Explode(10,CreateObject(PRNT));
    //Effect();
    turbo=1500;
    boosts++;
  }
  if(GetY()<-5000)
    Rain();
  turbo-=Distance(0,0,GetXDir(),GetYDir());
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);

Effect:
  var angle=Angle(0,0,GetXDir(),GetYDir());
  var x,y;
  x = Sin(angle, 80);
  y = Cos(angle, 80);
  SetVar(0,CreateObject(_WAV,0,-10, GetOwner()));
  ObjectCall(Var(0),"Launch",x,y,angle);
  
  x = Sin(angle+180, 80);
  y = Cos(angle+180, 80);
  SetVar(0,CreateObject(_WAV,0,-10, GetOwner()));
  ObjectCall(Var(0),"Launch",x,y,angle+180);
  return(1);
  
GetNumber:
  return(Pow(2,boosts+1));
  
Rain:
  for(var x=0; x<LandscapeWidth(); x+=LandscapeWidth()/100) {
    SetVar(0,CreateObject(_WAV,0,0,GetOwner()));
    SetPosition(x-5+Random(10),0, Var(0));
    ObjectCall(Var(0),"Launch",0,60,0,GetNumber());
  } 
  RemoveObject();
  return(1);

Hit:
  Sound("SonicFlint");
  
  for(var angle=0; angle<360; angle+=360/GetNumber()) {
    var x,y;
    x = Sin(angle+90, 80);
    y = -Cos(angle+90, 80);
    SetVar(0,CreateObject(_WAV,0,0,GetOwner()));
    SetPosition(GetX(),Sub(GetY(),10),Var(0));
    ObjectCall(Var(0),"Launch",x,y,angle+270,GetNumber());
  } 
  Explode(10);
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);
