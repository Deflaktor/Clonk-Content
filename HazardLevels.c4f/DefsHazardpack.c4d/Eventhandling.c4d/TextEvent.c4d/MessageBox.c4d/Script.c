/*-- MessageBox --*/

#strict

local messageShowObject, face;

Initialize:
  SetClrModulation(RGBa(255,255,255,128),this());
  SetFace(TH1_);
  Sound("RadioStatic",1);
  return(1);

SetFace:
  if(!Par(0)) {
    if(face)
      RemoveObject(face);
    SetPosition(132,87);
    return(1);
  }
  SetPosition(162,87);
  if(face)
    RemoveObject(face);
  face = CreateObject(Par(0), -112, 32);
  return(1);

Message:
  if(!messageShowObject)
    messageShowObject = CreateObject(THQ_);
  var x=0;
  var y=44;
  if(face) x=10;
  if(Par(1)==1)
    y=20;
  if(Par(1)==2)
    y=28;
  if(Par(1)==3)
    y=36;
  if(Par(1)==4)
    y=44;
  SetPosition(GetX()+x,GetY()+y,messageShowObject);
  messageShowObject->ShowMessage(Par(0),Par(2),Par(3),Par(4),Par(5),Par(6),Par(7),Par(8),Par(9));
  return(1);

Remove:
  RemoveObject(messageShowObject);
  RemoveObject(face);
  RemoveObject();
  return(1);

Delete:
  return(1);