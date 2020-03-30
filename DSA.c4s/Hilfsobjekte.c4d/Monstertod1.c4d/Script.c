Initialize:
  SetAction("Los");
  return(1);

Test:
  if(SetLocal(1,FindObject(0,-50,-50,100,100,OCF_Prey()))) SetAction("AbdiePost");
  return(1);

Erstellen:
  SetPosition(0,0);
  Message("Eine Stimme:|Mal schauen, ob ihr mit einer Horde Skeletten fertig werdet!!!",Local(1));    
  Music("finalfight");    
  CreateObject(_S09);
  CreateObject(_G02);
  RemoveObject();
  return(1);