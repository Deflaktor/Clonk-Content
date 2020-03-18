#strict
#include PRNT

//gesäubert von Jörn (mir) *g* und flgr jaja... *blubber*
Hit:
  if(ActIdle()) SetVar(0,5);
  if(SEqual(GetAction(),"JumpLeft")) SetVar(0,6);
  if(SEqual(GetAction(),"JumpRight")) SetVar(0,7);
  if(Equal(Var(0),5)) Split();
  if(Equal(Var(0),6)) JumpL();
  if(Equal(Var(0),7)) JumpR();
  return(1);
Split:
  SetVar(0,CreateContents(GetID(this())));
  SetVar(1,CreateContents(GetID(this())));
  SetOwner(GetOwner(),Var(0));
  SetOwner(GetOwner(),Var(1));
  Exit(Var(0),0,0,0,-2,-1);
  Exit(Var(1),0,0,0,2,-1);
  ObjectSetAction(Var(0),"JumpLeft");
  ObjectSetAction(Var(1),"JumpRight");
  Sound("Arrow"); 
  Explode(20);
  return(1);
JumpL:
  if(GreaterThan(GetActTime(),150)) return(Explode(20));
  SetXDir(-20);
  SetYDir(-10);
  Sound("Boing");
  Explode(20,CreateObject(PRNT,0,1));
  if(GetX()>LandscapeWidth()-2||GetX()<2)
    RemoveObject();
  return(1);
JumpR:
  if(GreaterThan(GetActTime(),150)) return(Explode(20));
  SetXDir(20);
  SetYDir(-10);
  Sound("Boing");
  Explode(20,CreateObject(PRNT,0,1));
  if(GetX()>LandscapeWidth()-2||GetX()<2)
    RemoveObject();
  return(1);
Smoke:
  if(GBackSolid()) return(Explode(20));
  if(InLiquid()) return(Bubble());
  return(1);

ContactLeft:
  Explode(20);
  return(1);

ContactRight:
  Explode(20);
  return(1);
  
  
