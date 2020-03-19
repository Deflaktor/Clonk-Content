/*-- Neues Objekt --*/

#strict

func Initialize() {
  SetAction("Create");
}

func Create() {
  /*var body = CreateObject(_YBB,0,0,GetOwner());
  body->Init();*/
  return(RemoveObject());
}