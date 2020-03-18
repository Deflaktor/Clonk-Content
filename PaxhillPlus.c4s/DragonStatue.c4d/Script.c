/*-- Drachenstatue --*/

#strict

static dragonBattle;

local startTime;

protected func Initialize() {
  SetAction("Waiting");	
}

protected func VisitorCheck() {
  if (!GetFlag(GF_Running())) return(1);
  if(!startTime)
    startTime = FrameCounter();
  if(FrameCounter() - startTime < 34*30)
    return(1);
  if(GetX()<LandscapeWidth()/2)
    return(Left());
  return(Right());
}

protected func Left() {
  if(!(dragonBattle & 2))
    while(Var(0)=FindObject(0, -GetX(), -GetY(), GetX()+40, LandscapeHeight(), OCF_CrewMember(), 0, 0, 0, Var(0))) 
      if(GetPlrSide(GetOwner(Var(0)))!=-1)
  	    return(Battle(2));
  if(dragonBattle & 2) {
    while(Var(0)=FindObject(0, -GetX(), -GetY(), GetX()+40, LandscapeHeight(), OCF_CrewMember(), 0, 0, 0, Var(0)))
	  if(GetPlrSide(GetOwner(Var(0)))!=-1)
	    Var(1)=1;
	if(!Var(1))
	  return(Peace(2));    
  }
}

protected func Right() {
  if(!(dragonBattle & 1))
    while(Var(0)=FindObject(0, -40, -GetY(), LandscapeWidth()-GetX()+40, LandscapeHeight(), OCF_CrewMember(), 0, 0, 0, Var(0))) 
      if(GetPlrSide(GetOwner(Var(0)))!=1)
  	    return(Battle(1));
  if(dragonBattle & 1) {
    while(Var(0)=FindObject(0, -40, -GetY(), LandscapeWidth()-GetX()+40, LandscapeHeight(), OCF_CrewMember(), 0, 0, 0, Var(0)))
	  if(GetPlrSide(GetOwner(Var(0)))!=1)
	    Var(1)=1;
	if(!Var(1))
	  return(Peace(1));
	}
}

public func Battle() {
  dragonBattle|=Par(0);
  Sound("DragonGrowl");
  return(SetAction("Rise"));
}

public func Peace() {
  dragonBattle&=~Par(0);
  if(!dragonBattle&&!importantBattleMusicEndFrame)
    PeaceMusic();
  return(1);
}

protected func Passing() {
  Sound("Gong");
  BattleMusic();
  return(1);
}
