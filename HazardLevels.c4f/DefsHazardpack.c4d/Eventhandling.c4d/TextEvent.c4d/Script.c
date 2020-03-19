#strict
#include T_1_
/* MessageEvent */

local messages, length, targets, nextMessageID, messageTime, messageActuator, messageBox, noTrigger, face;

protected func Initialize() {
  RemoveAllMessages();
  nextMessageID = -1;
  return(_inherited());
}

protected func AlternativeComment() {
  return(Local(0));
}

protected func Execute(object pActuator) {
  messageActuator = pActuator;
  nextMessageID = 0;
  messageTime = MessageDisplayTime();
  return(1);
}


public func ShowAllMessages() {
  noTrigger=true;
  Execute();
  return(1);
}


public func ShowChangeText(int index, string newText, int rows) {
  if(newText) {
    Local(index) = newText;
    Local(index+1) = rows;
  }
  ShowMessage(index/2, rows);
  ScheduleCall(this(), "HideMessage", 100, 0, index/2);
  return(1);
}

public func ShowMessage(int id, object pActuator) {
  var name = "wie auch immer Sie heißen";
  if(pActuator)
    name = GetName(pActuator);
  if(pActuator&&Local(2*id+1)==this())
    Message(Local(2*id), pActuator, name);
  else if(!Local(2*id+1)||GetType(Local(2*id+1))==C4V_Int()) {
    if(!messageBox) messageBox=CreateObject(TH0_);
    var rows;
    if(GetType(Local(2*id+1))==C4V_Int())
      rows = Local(2*id+1);
	if(face) messageBox->SetFace(face);
    messageBox->Message(Local(2*id), rows, name);
  } else
    Message(Local(2*id), Local(2*id+1), name);
  return(1);
}

public func HideMessage(int id, object pActuator) {
  if(pActuator&&Local(2*id+1)==this())
    Message("", pActuator);
  else if(!Local(2*id+1)||GetType(Local(2*id+1))==C4V_Int()) {
    if(messageBox) {
      if(Local(2*id+2)&&(!Local(2*id+1+2)||GetType(Local(2*id+1+2))==C4V_Int()))
        messageBox->Message("");
      else
        messageBox->Remove();
    }
  } else
    Message("", Local(2*id+1));
  return(1);
}

AddMessage:
  Local(2*length) = Par(0);
  Local(2*length+1) = Par(1);
  length++;
  return(length-1);

public func RemoveAllMessages() {
  for(var i=0;i<2*length+1;i++)
    Local(i) = 0;
  length = 0;
  return(1);
}

protected func Timer() {
  _inherited();
  if(nextMessageID<0)
    return(1);
  if(FindObject(TH0_)!=messageBox)
    return(1);
  ShowMessage(nextMessageID, messageActuator);
  messageTime--;
  if(messageTime<=0) {
    HideMessage(nextMessageID, messageActuator);
    nextMessageID++;
    if(nextMessageID>=length) {
      nextMessageID = -1;
      if(messageBox) messageBox->Remove();
      if(target&&!noTrigger) target->Trigger(messageActuator);
      if(noTrigger) noTrigger=false;
    }
    messageTime = MessageDisplayTime();
  }
  return(1);
}

SetFace:
  face=Par(0);
  return(1);

IsTriggerable:
  return(1);

MessageDisplayTime:
  return(20);
  