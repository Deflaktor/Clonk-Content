/*-- Blitzfalle --*/

#strict

local obj,obj2;

Initialize:
  SetOwner(-1);
  return(1);

ControlUp:
  Enter(FindObject(0,-10,-10,20,20,OCF_CrewMember()));
  return(1);

Activate:
  CreateMenu(FA_1,Par(0));
    AddMenuItem("Stellen","Stellen",SM_1,Par(0));
  return(1);

Stellen:
  if(GetDir(Contained())==DIR_Right()) Exit(0,20);
  if(GetDir(Contained())==DIR_Left()) Exit(0,-20);
  SetAction("Gestellt");
  Message("Falle gestellt",this());
  return(1);

Check4Living:
  if(obj=FindObject(CLON,-4,-12,8,12,OCF_CrewMember(),0,0,NoContainer()))
    return(SetAction("Blow"));
  if(obj=FindObject(CLSK,-4,-12,8,12,OCF_CrewMember(),0,0,NoContainer()))
    return(SetAction("Blow"));
  if(obj=FindObject(CLSH,-4,-12,8,12,OCF_CrewMember(),0,0,NoContainer()))
    return(SetAction("Blow"));
  if(GetActTime()>1800)
    RemoveObject();
 return(1);

Blow:
  SetVar(1,obj);
  while(SetVar(2,FindOtherContents(CHST,Var(1)))) Exit(Var(2),0,0,Random(360),0,0);
  SetVar(0,CreateObject(obj2=BLOW,0,-2));
  SetOwner(GetOwner(obj),Var(0));
  ObjectCall(Var(0),"Init",this());
  PrivateCall(obj,"NoSee");
  return(RemoveObject());

Ende:
  SetAction("Idle");
  RemoveObject();
  return(1);