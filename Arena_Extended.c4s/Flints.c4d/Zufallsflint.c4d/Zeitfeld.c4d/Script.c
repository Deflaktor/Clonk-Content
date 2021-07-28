#strict

Initialize:
SetAction("Blast");
SetCon(200);
return(1);

CreateHelper:
  SetVar(0,CreateObject(_SDH));
  SetLocal(0,Par(0),Var(0));
  SetLocal(1,this(),Var(0));
  SetLocal(2,GetXDir(Par(0)),Var(0));
  SetLocal(3,GetYDir(Par(0)),Var(0));
  SetLocal(4,GetX(Par(0)),Var(0));
  SetLocal(5,GetY(Par(0)),Var(0));
  if(SEqual(GetAction(Par(0)),"Travel")) {
    SetLocal(6,Local(0,Par(0)),Var(0));
    SetLocal(7,Local(1,Par(0)),Var(0));
    SetLocal(0,0,Par(0));
    SetLocal(1,0,Par(0));
  }
  SetLocal(69,1,Par(0));
  return(1);

Activity:
SetLocal(3,Sum(Local(3),1));
if (Local(3)>80)
  return(Remove());

while(SetVar(0,FindObject(0,-GetCon()/2,-GetCon()/2,GetCon(),GetCon(),0,0,0,NoContainer(),Var(0))))
  //if(GetCategory(Var(0)) & C4D_Object()||GetCategory(Var(0)) & C4D_Living())
    if(!SEqual(GetProcedure(Var(0)),"ATTACH"))
      if(!Local(69,Var(0)))
        if(GetXDir(Var(0))!=0||GetYDir(Var(0))!=0)
          if(GetOwner()!=GetOwner(Var(0)) || !(GetOCF(Var(0)) & OCF_CrewMember()))
            CreateHelper(Var(0));

//SetVar(2,Random(360));
//while(LessThan(Var(2),361)) {
//  LaunchLightning(GetX(),GetY(),Sin(Var(2),15),20,Cos(Var(2),15),20);
//  SetVar(2,Sum(Var(2),15));
//}


return(1);

Remove:
return(RemoveObject());