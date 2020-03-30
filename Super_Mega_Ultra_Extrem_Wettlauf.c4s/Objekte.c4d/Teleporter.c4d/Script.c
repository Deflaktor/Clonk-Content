/*-- Neues Objekt --*/

#strict

Teleport:
  while(Var(0)=FindObject(CLNK,0,LandscapeHeight()-5,LandscapeWidth(),50,0,0,0,NoContainer(),Var(0))) ObjectCall(Var(0),"Verschwinde");
  while(Var(0)=FindObject(PM7K,0,LandscapeHeight()-2,LandscapeWidth(),50,0,0,0,NoContainer(),Var(0))) ObjectCall(Var(0),"Verschwinde");
  while(Var(0)=FindObject(PN7K,0,LandscapeHeight()-2,LandscapeWidth(),50,0,0,0,NoContainer(),Var(0))) ObjectCall(Var(0),"Verschwinde");
  while(Var(0)=FindObject(BIK1,0,LandscapeHeight()-5,LandscapeWidth(),50,0,0,0,NoContainer(),Var(0))) ObjectCall(Var(0),"Verschwinde");
  while(Var(0)=FindObject(HORS,0,LandscapeHeight()-10,LandscapeWidth(),100,0,0,0,NoContainer(),Var(0))) ObjectCall(Var(0),"Verschwinde");
  //while(Var(0)=FindObject(0,0,LandscapeHeight()-5,LandscapeWidth(),50,0,0,0,NoContainer(),Var(0))) RemoveObject(Var(0));
  return(1);
