/* Mini KI */

#strict
#include KIL1

ExplodeKamikaze:
  SetVar(0,CreateObject(NEBB,0,0,GetOwner()));
  if(died == 2) {
    SetOwner(killedBy, Var(0));
  } else {
    SetOwner(GetOwner(), Var(0));
  }
  ObjectCall(Var(0),"BlowUp");
  return(1);

ExplodeDistance:
  return(50);

Initialize:
  _inherited();
  DoCon(500);
  weap=KAZE;
  graber = false;
  return(0);
  
CheckKamikaze:
  if(weap == KAZE)
  {
    SetAction("KamikazeWalk");
    return(1);
  }
  ResetPhysical();
  return(1);

if(GetAction() S= "Dead") return(0);
if(Par(0) != GetOwner())
while(SetVar(1,FindObject(SDCL,0,0,0,0,0,0,0,0,Var(1))))
  if(GetOwner(Var(1))==Par(0)) {
    SetLocal(0,Local(0,Var(1))+1,Var(1));
    SetLocal(1,Var(1));
  }
SetWealth(Par(0),GetWealth(Par(0))+25);
return(0);

GetValue:
  return(30);

Death:
  SetCommand(this(),"None");
  Sound("Death");
  var threattype = Random(11);
  if(threattype == 10)
  CreateObject(S582,0,0,GetOwner());
  if(threattype < 10)
{
  CreateObject(ST58,0,0,GetOwner());
  CreateObject(ST58,0,0,GetOwner());}
  var ang, obj, xdir;
  var lev;
  lev = 50;
  for(var i=0;i<5;i++) {
    ang=Random(360);
    SetR(Random(360),obj=CreateObject(ST58,0,0,GetOwner()));
    SetXDir(xdir=Cos(ang,lev)+RandomX(-3,3),obj);
    SetYDir(Sin(ang,lev)+RandomX(-3,3),obj);
    SetRDir((10+Random(21))*xdir/Abs(xdir),obj);
  }
if(Local(9)==0)
  if(WeapID() == KAZE)
    ExplodeKamikaze();
    GameCall("RelaunchKi",GetOwner());
  return(1);