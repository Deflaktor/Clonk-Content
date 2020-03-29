#strict
#appendto TU1_

public func Event1(object pActuator) {
  primaryObjective=GetTarget();
  return(1);
}

public func Event2(object pActuator) {
  secondaryObjective=GetTarget();
  return(1);
}

public func Event3(object pActuator) {
  SetXDir(0, pActuator);
  return(1);
}

public func Event4(object pActuator) {
  SetLocal(Local(0),Local(1),GetTarget());
  return(1);
}

public func Event5(object pActuator) {
  ChangeDef(Local(0), GetTarget());
  ObjectCall(GetTarget(), "Initialize");
  return(1);
}

public func Event6(object pActuator) {
  cardObjective2=GetTarget();
  return(1);
}

public func Event7(object pActuator) {
  cardObjective3=GetTarget();
  return(1);
}

public func Event8(object pActuator) {
  optionalObjective=GetTarget();
  return(1);
}

public func Event9(object pActuator) {
  cardObjective4=GetTarget();
  return(1);
}

public func Event10(object pActuator) {
  cardObjective1=GetTarget();
  return(1);
}

public func Event11(object pActuator) {
  ObjectCall(GetTarget(), Local(0));
  return(1);
}

public func Event12(object pActuator) {
  Var(0)=FindObject(_AP0,0,0,-1,-1);
  Var(1)=FindObject(_SBL,0,0,-1,-1);
  SetOwner(GetOwner(pActuator), Var(0));
  SetOwner(GetOwner(pActuator), Var(1));
  SetVisibility(VIS_Owner() | VIS_God(), Var(0));
  SetVisibility(VIS_Owner() | VIS_God(), Var(1));
  SetLocal(0,1,Var(0));
  return(1);
}

public func Event13(object pActuator) {
  if(Local(0)) GameCall("SetDeployPlayerIfHeDiesInSky");
  else GameCall("ResetDeployPlayerIfHeDiesInSky");
}

public func Event14(object pActuator) {
  // Local(0) = 1: Got Power-Suit
  // Local(0) = 2: Got Gravity-Suit
  if(playerRespawnID==0||playerRespawnID==HZCK) {
    if(Local(0)==1)
	  playerRespawnID=HCK3;
	if(Local(0)==2)
	  playerRespawnID=HCK2;
  } else if(playerRespawnID==HCK2) {
    if(Local(0)==1)
	  playerRespawnID=HCK4;
  } else if(playerRespawnID==HCK3) {
	if(Local(0)==2)
	  playerRespawnID=HCK4;
  } else if(playerRespawnID==HCK4) {
    
  }
  var i,j;
  for (j = GetPlayerCount(); j > 1; i++) 
    if (GetPlayerName(i) && (i != GetOwner(pActuator)))
    {
	  if(Local(0)==1)
	    CreateContents(_POW,GetCrew(i));
      if(Local(0)==2)
	    CreateContents(POW2,GetCrew(i));
      --j;
    }
}

public func Event15(object pActuator) {
  cardObjective5=GetTarget();
  return(1);
}

// Remove all ForceFields
public func Event16(object pActuator) {
  var obj;
  while(obj = FindObject(FCWS)) RemoveObject(obj);
  while(obj = FindObject(FBRS)) RemoveObject(obj);
  return(1);
}

// Nachschub Munition im Raum
public func Event17(object pActuator) {
  var raum = GetTarget();
  if(ContentsCount(_AP7,raum)<1) CreateContents(_AP7,raum);
  if(ContentsCount(_AP3,raum)<1) CreateContents(_AP3,raum);
  if(ContentsCount(_AP5,raum)<1) CreateContents(_AP5,raum);
  if(ContentsCount(_PP6,raum)<1) CreateContents(_PP6,raum);
  if(ContentsCount(_AP2,raum)<1) CreateContents(_AP2,raum);
  return(1);
}