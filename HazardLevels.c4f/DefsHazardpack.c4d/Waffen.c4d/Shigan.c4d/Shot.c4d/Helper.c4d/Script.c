/*-- Neues Objekt --*/

#strict

// HARM:
// Local(1): Time Left
// Local(2): Smoke Color

// BLOW:
// Local(1): Release
// Local(2): Starting Health of Target
// Local(3): Time to Blow

Dmg:
  // PAR(0) = HARM
  if(Par(0))
    return(1*12);
  return(0);

DoHurt:
  DoEnergy(-Dmg(1)/12,Par(0));
  if(Local(2)) DoEnergy(-Dmg(1)/12,Par(0));
  if(Local(2))
    CreateParticle("Smoke", 0,0, 0,0, 40, Local(2));
  else
    Smoke (0, 0, 4);
  return(1);

Harm:
  if(!GetActionTarget())
    return(RemoveObject());
  SetPosition(GetX(GetActionTarget()),GetY(GetActionTarget()));
  if(!GetAlive(GetActionTarget()))
    return(RemoveObject());
  DoHurt(GetActionTarget());
  Local(1)++;
  if(Local(1)>12)
    RemoveObject();
  return(1);
  

BlowHim:
  Local(3)++;
  if(Local(3)>Local(2)/15) {
    DoCon(+1+Max(GetCon()-100,0),Par(0));
    Sound("Scrape");
    if(Local(2)<10)
      DoCon(+10-Local(2),Par(0));
    Local(3)=0;
  }
  if(GetCon(Par(0))>200) {
    Par(0)->Platzen();
    RemoveObject();
  }
  return(1);

Release:
  while(GetCon(Par(0))>100&&GetCon(Par(0))<105)
    DoCon(-1,Par(0));
  if(GetCon(Par(0))>105)
    DoCon(-5,Par(0));
  else
    RemoveObject();
  return(1);

Blow:
  if(!Local(2))
    Local(2) = GetEnergy(GetActionTarget());
  if(!GetActionTarget())
    return(RemoveObject());
  SetPosition(GetX(GetActionTarget()),GetY(GetActionTarget()));
  if(!GetAlive(GetActionTarget()))
    return(RemoveObject());
  if(Local(1))
    return(Release(GetActionTarget()));
  BlowHim(GetActionTarget());
  return(1);
  
Remove:
  if(GetAction()S= "Blow")
    Local(1)=1;
  else
    RemoveObject();
  return(1);