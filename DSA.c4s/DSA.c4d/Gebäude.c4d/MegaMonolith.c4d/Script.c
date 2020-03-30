#strict

Initialize:
  /*------ Steinspeicher leeren ------*/
  SetAction("Wait");
  return(1);

ControlUp:
  SetLocal(0,Par(0));
  if(SEqual(GetAction(),"Wait")) Anfang();
  return(1);

Anfang:
  SetAction("burk");
  CreateMenu(GetID(),Local(0),this(),0,"Wohin möchtest du?",0,1);
  SetMenuSize(ContentsCount(),1,Local(0));
  var i;
  i=0;
  while(Contents(i)!=0) {
    AddMenuItem(Local(5,Contents(i)), "Teleport", GetID(Contents(i)), Local(0), 0, Contents(i));
    i++;
  }
  return(1);

Teleport:
  SetLocal(1,Par(1));
  ObjectSetAction(Par(1),"beam");
  SetAction("busy");
  return(1);

Beam:
  SetVar(0,GetX( Local( 0,Local(1) ) ) );
  SetVar(1,GetY( Local( 0,Local(1) ) ) );
  SetPosition(Var(0),Var(1),Local(0));
  return(1);

RejectCollect:
  if(Equal(Par(0),MS3A))  return(0);
  return(1);

