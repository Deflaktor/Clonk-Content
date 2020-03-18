/*-- Keine Grenzen! --*/

#strict

Initialize:
 SetPosition();
 if(Var(0)=FindObject(GetID())) {
   SetLocal(3,0,Var(0));
   return(RemoveObject());
 }
 DrawMaterialQuad("Earth-RIDGE",0,LandscapeHeight()-42,LandscapeWidth(),LandscapeHeight()-42,LandscapeWidth(),LandscapeHeight(),0,LandscapeHeight(), 1);
 return(1);
 
Remove:
 DrawMaterialQuad("Granite-Rough",0,LandscapeHeight()-42,LandscapeWidth(),LandscapeHeight()-42,LandscapeWidth(),LandscapeHeight(),0,LandscapeHeight());
 while(Var()=FindObject(0,0,LandscapeHeight()-60,LandscapeWidth(),80,0,0,0,0,Var()))
   if(GetY(Var()) > LandscapeHeight()-42-GetDefCoreVal("Height","DefCore",GetID(Var()))/2,Var())
     SetPosition(GetX(Var()),LandscapeHeight()-42-GetDefCoreVal("Height","DefCore",GetID(Var()))/2,Var());
 RemoveObject();
 return(1);

Check:
  SetLocal(3,Sum(Local(3),1));
  if (Local(3)>6000)
    return(Remove());
  // Oben
  while(Var()=FindObject(0,0,0,LandscapeWidth(),200,0,0,0,0,Var()))
    if(!(GetCategory(Var())&C4D_StaticBack()))
      if(SlowCheckTop(Var()) || FastCheckTop(Var()))
         SetPosition(GetX(Var()),LandscapeHeight()-GetDefCoreVal("Height","DefCore",GetID(Var()))/2,Var());

  // Links
  while(Var()=FindObject(0,0,0,200,LandscapeHeight(),0,0,0,0,Var()))
    if(!(GetCategory(Var())&C4D_StaticBack()))
      if(SlowCheckLeft(Var()) || FastCheckLeft(Var()))
        SetPosition(LandscapeWidth()-GetDefCoreVal("Width","DefCore",GetID(Var()))/2,GetY(Var()),Var());

  // Rechts
  while(Var()=FindObject(0,LandscapeWidth()-200,0,200,LandscapeHeight(),0,0,0,0,Var()))
    if(!(GetCategory(Var())&C4D_StaticBack()))
      if(SlowCheckRight(Var()) || FastCheckRight(Var()))
        SetPosition(GetDefCoreVal("Width","DefCore",GetID(Var()))/2,GetY(Var()),Var());

  // Unten
  while(Var()=FindObject(0,0,LandscapeHeight()-200,LandscapeWidth(),205,0,0,0,0,Var()))
    if(!(GetCategory(Var())&C4D_StaticBack())) {
	  if(SlowCheckBottom(Var())) {
		SetPosition(GetX(Var()),GetDefCoreVal("Height","DefCore",GetID(Var()))/2,Var());
	  } else if(FastCheckBottom(Var())) {
	    if(GetOCF(Var()) & OCF_CrewMember()) {
	      if(GetComDir(Var(0))==COMD_Right())
		    SetXDir(GetXDir(Var(0)) + 1, Var(0));
	      if(GetComDir(Var(0))==COMD_Left())
		    SetXDir(GetXDir(Var(0)) - 1, Var(0));
		}
        SetPosition(GetX(Var()),GetDefCoreVal("Height","DefCore",GetID(Var()))/2,Var());
	  }
	}
		  
  while(Var()=FindObject(0,0,0,0,0,OCF_CrewMember(),0,0,0,Var()))
    if(GetYDir(Var(0))>500) {
	  if(GetComDir(Var(0))==COMD_Right())
		SetXDir(GetXDir(Var(0)) + 1, Var(0));
	  if(GetComDir(Var(0))==COMD_Left())
		SetXDir(GetXDir(Var(0)) - 1, Var(0));
	}
  if(Local(0)>=0)
    if(GetMaterialCount(Material("Earth"))<600) {
      DrawMaterialQuad("Earth-RIDGE",100,LandscapeHeight()-42,LandscapeWidth()-100,LandscapeHeight()-42,LandscapeWidth()-100,LandscapeHeight(),100,LandscapeHeight(), 1);
	  Local(0)=-500;
    }
  Local(0)+=1;
  return(1);
  
Warp:
  return(1);
  
PathFreeCheck:
  if(PathFree(GetX(Par()),GetY(Par()),BoundBy(GetX(Par(0))+GetXDir(Par(0))/5,3,LandscapeWidth()-3),GetY(Par())+GetYDir(Par())/5))
    return(1);
  return(0);

SlowCheckLeft:
  if(GetX(Par())-GetDefCoreVal("Width","DefCore",GetID(Par()))/2<2 && GetX(Par()) < 40)
    if(GetXDir(Par()) < 0 || GetComDir(Par())==COMD_Left())
	  return(1);
  return(0);
  
FastCheckLeft:
  if(GetXDir(Par()) < 0 && GetX(Par(0)) <= -GetXDir(Par())/5)
    if(PathFreeCheck(Par()))
	  return(1);
  return(0);
  
SlowCheckRight:
  if(GetX(Par())+GetDefCoreVal("Width","DefCore",GetID(Par()))/2>LandscapeWidth()-2 && GetX(Par()) > LandscapeWidth()-40)
    if(GetXDir(Par()) > 0 || GetComDir(Par())==COMD_Right())
	  return(1);
  return(0);
  
FastCheckRight:
  if(GetXDir(Par())>0 && GetX(Par(0)) >= LandscapeWidth()-GetXDir(Par())/5)
    if(PathFreeCheck(Par()))
	  return(1);
  return(0);
  
SlowCheckTop:
  if(GetY(Par())-GetDefCoreVal("Height","DefCore",GetID(Par()))/2<2 && GetY(Par()) < 40)
    if(GetYDir(Par()) < 0 || GetComDir(Par())==COMD_Up())
	  return(1);
  return(0);
  
FastCheckTop:
  if(GetYDir(Par())<0 && GetY(Par(0)) <= -GetYDir(Par())/5)
    if(PathFreeCheck(Par()))
	  return(1);
  return(0);
  
SlowCheckBottom:
  if(GetY(Par())+GetDefCoreVal("Height","DefCore",GetID(Par()))/2>LandscapeHeight()-3 && GetY(Par()) > LandscapeHeight()-40)
    if(GetYDir(Par()) > 0 || GetComDir(Par())==COMD_Down())
	  return(1);
  return(0);
  
FastCheckBottom:
  if(GetYDir(Par())>=0 && GetY(Par(0)) >= LandscapeHeight()-GetYDir(Par())/5)
    if(PathFreeCheck(Par()))
	  return(1);
  return(0);