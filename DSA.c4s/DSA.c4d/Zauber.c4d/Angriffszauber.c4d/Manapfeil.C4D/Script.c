//Author:major}

#strict

local owner;

CastMeteor:
  if (GetComDir() == COMD_Left()) CastLeft();
  if (GetComDir() == COMD_Right()) CastRight();
  return(1);

CastRight:
  SetLocal(0,+200);
  SetXDir(30,SetLocal(1,CreateObject(HHX9,20,5)));
  SetPlrView (owner,Local(1)); 
  SetAction("Travel");
  return(1);

CastLeft:
  
  SetLocal(0,-200);
  SetXDir(-30,SetLocal(1,CreateObject(HHX9,-20,5)));
  SetPlrView (owner,Local(1));
  SetAction("Travel");
  return(1);

Activate:
 owner=GetOwner(Par());
  SetLocal(2,GetY());
  if (GetDir(Par(0))==DIR_Left()) SetComDir(COMD_Left());
  if (GetDir(Par(0))==DIR_Right()) SetComDir(COMD_Right());
  Sound("Magic1");
  CastMeteor();
  return(1);

Travel:

  if(!Local(1))
     return(RemoveObject());
  SetPosition(GetX(Local(1)),Local(2),Local(1));
  SetXDir(Local(0),Local(1));
  
  return(1);