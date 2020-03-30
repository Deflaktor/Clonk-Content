#strict

public Activate:
 
SetVar(1,Par());
if(Par(1))
  SetVar(1,Par(1));


while(SetVar(0,FindObject(0,-500,-500,1000,1000,OCF_CrewMember(),0,0,NoContainer(),Var())))
       if(!Hostileto(GetOwner(Var()),GetOwner(Var(1))))
         Warp(Var());




  // Den zaubernden Clonk im Zauberturm warpen
  if (Par(1))   
      {
      Warp(Par(1));
      RemoveObject();
      return();}

  // Sonst das aufrufende Objekt (zaubernder Clonk drauﬂen) warpen
 
      Warp(Par());
      RemoveObject();
      return(1);

Warp:
  Sound("Magic1");
  ObjectCall(CreateObject(MWP2,0,0,GetOwner(Par())),"Activate",Par());
  
  return(1);
