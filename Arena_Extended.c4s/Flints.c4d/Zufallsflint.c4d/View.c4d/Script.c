#strict
/* Anzeige */

/* Hilfe für den Zufallsflint */

RandomHelps:
  SetAction("Count4Remove");
  return(1);

Remove:
  RemoveObject();
  return(1);
  
Litten:
    if(!Local(0))
	  return(1);
	for(var i=0;i<3;i++)
      if(SetLocal(1,FindObject(0,0,0,0,0,OCF_Collectible(),0,0,0,Local(1)))) 
        LitUp(Local(1));
	return(1);
	
  
LitUp:
  Var(0)=Par(0);
  if((GetOCF(Var(0)) & OCF_Collectible()) != 0) {
    if(!ObjectCall(Var(0), "NoShiftOwner"))
      SetOwner(GetOwner(),Var(0));
    if(!ObjectCall(Var(0),"Hurt", Contained(Var(0)) ) && GetID(Var(0)) != ST58 && GetID(Var(0)) != S658 && GetID(Var(0)) != CHST) {
      ObjectCall(Var(0),"Activate", GetCrew(0,GetOwner()));
      ObjectCall(Var(0),"Hit");
    }
  }
  /*if(GetID(Var(0))==CHST||GetID(Var(0))==S582||GetID(Var(0))==ST58||GetID(Var(0))==S658)
    return(0);*/
  return(1);
  