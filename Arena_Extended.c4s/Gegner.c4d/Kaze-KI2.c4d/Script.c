/* Mini KI */

#strict
#include KIL1

ExplodeKamikaze:
  if(died == 2) {
    CreateObject(PRNT,0,3,killedBy)->Explode(70);
	CreateObject(PRNT,0,3,killedBy)->Explode(60);
  } else {
    Explode(70,CreateObject(PRNT,0,3));
    Explode(60,CreateObject(PRNT,0,3));
  }
  return(1);
  
ExplodeDistance:
  return(30);
  
Initialize:
  _inherited();
  DoCon(100);
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
  
GetValue:
  return(10);

Death:
  SetCommand(this(),"None");
  Sound("Death");
  var threattype = Random(11);
  if(threattype == 10)
  CreateObject(S582,0,0,GetOwner(this()));
  if(threattype < 10)
{
  CreateObject(ST58,0,0,GetOwner(this()));
  CreateObject(ST58,0,0,GetOwner(this()));}
if(Local(9)==0)
  if(WeapID() == KAZE)
    ExplodeKamikaze();
    GameCall("RelaunchKi",GetOwner());
  return(1);
