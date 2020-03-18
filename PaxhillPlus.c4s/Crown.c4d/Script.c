#strict

protected func Initialize()
{
  // Blinkaktivität setzen
  SetAction("Glitter0");
  return(1);
}

CalcValue:
  if(Local()==GetPlrSide(Par(1)))
    return(0);
  return(GetDefValue(GetID()));

local lastBase, lastEnemyCarrier;

Entrance:
  if(GetOCF(Par(0)) & OCF_CrewMember()) {
    if(Local()!=GetPlrSide(GetOwner(Par()))) {
      ActionMusic();
	  lastEnemyCarrier = Par(0);
	  return(1);
    } else if (lastEnemyCarrier) {
      lastEnemyCarrier = 0;
	  SwitchToDefaultMusic();
	}
	lastEnemyCarrier = 0;
  }
  return(1);
  
Check:
  if(GetBase(Contained())!=-1)
    lastBase=Contained();
  else
    lastBase=0;
  return(1);
  
Sale:
  if(Local()==GetPlrSide(Par())) {
    var obj;
	obj=CreateContents(GetID(),lastBase);
	SetOwner(GetOwner(), obj);
	obj->Local(0)=Local(0);
    return(Sound("Error"));
  }
  return(GameCall("CrownLost", this()));
  
// Auftreffsound
protected func Hit() { Sound("Crystal*"); }

// Verlust
protected func Destruction() {
  if(!lastBase) {
    var obj,x,y;
	x=BoundBy(GetX(), 0, LandscapeWidth());
	y=BoundBy(GetY(), 0, LandscapeHeight());
	obj=CreateObject(GetID(),x-GetX(),y-GetY(),GetOwner());
	obj->Local(0)=Local(0);
  }
}

// Aktivität
protected func Glittering()
{
  if(lastEnemyCarrier) {
    ActionMusic();
	  if(!GetAlive(lastEnemyCarrier)) {
		/*var enemiesNearby = false;
		while(Var(0)=FindObject(0,-400,-400,800,800,OCF_CrewMember(),0,0,0,Var(0))) {
		  if(GetAlive(Var(0)))
			if(Local()!=GetPlrSide(GetOwner(Var())))
			  enemiesNearby = true;
		}
		if(!enemiesNearby) {*/
		  lastEnemyCarrier = 0;
		  SwitchToDefaultMusic();
		//}
	  }
  }

	// Steckt fest?
	if (Stuck()) SetPosition(GetX(), GetY()-1);
  SetAction(Format("Glitter%d", Random(5)));
  
}

private func ActionMusic() {
  // Krone über die 2/3 des Spielfelds überquert -> Panik
  if(!(currentBattleMusic S= "@ifYouCanUseADoorKnob.ogg")) {
    // Linke Krone
	/*  if(Local(0)==-1)
		if(GetX()>LandscapeWidth()*2/3) {
		  importantBattleMusicEndFrame=0;
		  return(Music("@ifYouCanUseADoorKnob.ogg",0,2));
		}*/
	// Rechte Krone
	/*  if(Local(0)==1)
		if(GetX()<LandscapeWidth()*1/3) {
		importantBattleMusicEndFrame=0;
		  return(Music("@ifYouCanUseADoorKnob.ogg",0,2));
		}*/
  }
  if(!(currentBattleMusic S= "@Ruinion.ogg")&&!(currentBattleMusic S= "@CamelsStrawsAndBacks.ogg")) {
  	    if(Random(2))
          Music("@Ruinion.ogg",0,1);
		else
		  Music("@CamelsStrawsAndBacks.ogg",0,1);
		return(1);
  }
}

// Einsammelbar?
protected func RejectEntrance()
{
  // Flag gesetzt?
  if (!GetFlag(GF_SensCr())) return();
  // Aus anderen Containern heraus (feindliche Clonks, ...) kein Problem
  if (Contained()) return();
  // ...oder direkt von feindlichen Clonks
  if (~GetOCF(Par()) & OCF_CrewMember()) return(1);
  // Und nicht von eigenen
  return (Local()==GetPlrSide(GetOwner(Par())));
}
