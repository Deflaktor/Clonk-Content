#strict

local eventcounter;

protected Initialize:
  SetAction("Initialize");
  // Position
  SetPosition();
  return(1);

Initialized:
  // Plazierungsfaktor ermitteln
  Local(0)=ObjectCount(GetID())+1;
  // Andere Objekte des gleichen Typs entfernen
  while(Var(1)=FindObject(GetID()))
    RemoveObject(Var(1));
  SetLocal(1,(Local(0)*-3)+40);
  // Steuerungsaktion
  SetAction("Active");
  return(1);

EventCheck:
  if(!GodDa())
    SetLocal(1,Local(1)-1);
  if(Local(1)<=0) {
    ResetTimer();
    Event();
  }
  return(1);

Event:
  eventcounter++;
  if(eventcounter%8==0)
    return(DoppelEvent());
  GameCall("Event");
  return(1);
    
DoppelEvent:
  Message("     Es ist Zeit für ein Doppel-Ereignis!     ");
  Sound("ping",1);
  return(SetAction("Event1"));

Event1:
  return(GameCall("Event"));
  
EventUnd:
  Message("                    Und...                    ");
  return(1);
  
Event2:
  return(GameCall("Event"));
  
ResetTimer:
  SetLocal(1,(Local(0)*-3)+40);
  return(1);
  
GodDa:
  return(Local(0,FindObject(MNTK)));